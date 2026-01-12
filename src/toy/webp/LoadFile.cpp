#include <webp/decode.h>
#include <webp/mux_types.h>
#include <webp/demux.h>
#include "toy/Catch.hpp"
#include "toy/math/SafeInt.hpp"
#include "toy/file/File.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/webp/LoadFile.hpp"

namespace toy{
namespace webp{

class WebpObj
{
	public:

		WebpObj()
		{
			if ( ! WebPInitDecoderConfig(&_config))
			{
				toy::Logger<<"Library version mismatch!"<<toy::NewLine;
				throw toy::Exception(TOY_MARK);
			}

			_config.options.dithering_strength = 50;
			_config.options.alpha_dithering_strength = 100;
		}

		~WebpObj()
		{
			WebPFreeDecBuffer((WebPDecBuffer*)_pic);
			_pic = nullptr;
			WebPDataClear(&_data);
			WebPDemuxReleaseIterator(&_curr_frame);
			WebPDemuxReleaseIterator(&_prev_frame);
		//	WebPDemuxReleaseChunkIterator(&kParams.iccp);
			WebPDemuxDelete(_dmux);
			_dmux = nullptr;
		}

		void read(const std::vector<uint8_t> &buffer)
		{
			uint8_t *newData = (uint8_t*)std::malloc(buffer.size());

			std::memcpy(newData,buffer.data(),buffer.size());

			_data.bytes = newData;
			_data.size = buffer.size();

			if (!WebPGetInfo(_data.bytes, _data.size, nullptr, nullptr))
			{
				toy::Logger<<"Input file doesn't appear to be WebP format."<<toy::NewLine;
				throw toy::Exception(TOY_MARK);
			}

			if ((_dmux = WebPDemux(&_data))==nullptr)
			{
				throw toy::Exception(TOY_MARK);
			}

			_width           = WebPDemuxGetI(_dmux, WEBP_FF_CANVAS_WIDTH);
			_height          = WebPDemuxGetI(_dmux, WEBP_FF_CANVAS_HEIGHT);
			_loopCount       = WebPDemuxGetI(_dmux, WEBP_FF_LOOP_COUNT);
			_backGroundColor = WebPDemuxGetI(_dmux, WEBP_FF_BACKGROUND_COLOR);
		}

		void decode(::toy::ImageBuffer *imageBuffer)
		{
			imageBuffer->_setFormat(toy::RGBA);
			imageBuffer->_setWidth( toy::math::SafeInt<uint32_t>(_width,TOY_MARK));
			imageBuffer->_setHeight(toy::math::SafeInt<uint32_t>(_height,TOY_MARK));

			if ( !WebPDemuxGetFrame(_dmux, 0, &_curr_frame) )
			{
				throw toy::Exception(TOY_MARK);
			}

			WebPDemuxNextFrame(&_curr_frame);

			_config.output.colorspace = MODE_RGBA;

			if ( WebPDecode(_curr_frame.fragment.bytes, _curr_frame.fragment.size, &_config) != VP8_STATUS_OK )
			{
				throw toy::Exception(TOY_MARK);
			}

			if ( imageBuffer->_getAllocator()->size((_width*_height)*4)==false )  // Allocate more memory. May be we need it later.
			{
				throw toy::Exception(TOY_MARK);
			}

			_pic = &_config.output;

			std::memcpy(imageBuffer->_data(),_pic->u.RGBA.rgba,(_width*_height)*4);
		}

		void clearPreviousFrame()
		{
			auto prev = &_prev_frame;
			prev->width = _width;
			prev->height = _height;
			prev->x_offset = prev->y_offset = 0;
			prev->dispose_method = WEBP_MUX_DISPOSE_BACKGROUND;
		}

	private:

		WebPData               _data;
		WebPDemuxer*           _dmux = nullptr;
		WebPIterator           _curr_frame;
		WebPIterator           _prev_frame;
		int                    _width = 0;
		int                    _height = 0;
		int                    _loopCount = 0;
		uint32_t               _backGroundColor = 0;
		const WebPDecBuffer*   _pic;
		WebPDecoderConfig      _config;
};

static void LoadWholeImage(std::vector<uint8_t> *buffer,::toy::File *pIO)
{
	std::vector<uint8_t>      temp(128,0);

	pIO->seek(SEEK_SET,0);

	uint32_t  size = 0;

	for (;;)
	{
		size = pIO->read(temp.data(),128);

		if (size!=128)
		{
			temp.resize(size);
		}

		// buffer = buffer + temp
		buffer->insert(buffer->end(), temp.begin(), temp.end());

		if ( pIO->isEnd()) return;
	}
}

static void LoadGoogleWebp(::toy::File *pIO,::toy::ImageBuffer *imageBuffer)
{
	std::vector<uint8_t>      buffer;

	LoadWholeImage(&buffer,pIO);

	if ( buffer.size()==0 ) throw toy::Exception(TOY_MARK);

	WebpObj   obj;

	obj.read(buffer);

	obj.clearPreviousFrame();

	obj.decode(imageBuffer);
}

bool LoadWebp(::toy::File *pIO,::toy::ImageBuffer *imageBuffer)
{
	try
	{
		LoadGoogleWebp(pIO,imageBuffer);
	}
	catch(std::exception &e)
	{
		toy::Catch(e);
		return false;
	}

	return true;
}

}}
