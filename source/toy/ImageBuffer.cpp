#include <cstdlib>
#include <cstring>
#include "toy/ImageBuffer.hpp"
#include "toy/Math.hpp"

namespace toy{

static inline void GREY_to_RGBA( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data + size * 4;
	uint8_t  *pp2 = data + size;
	uint8_t  color = 255;

	do
	{
		pp1 -= 4;
		pp2 -= 1;

		color = *pp2==0 ? 0 : 255;

		pp1[2] = color;
		pp1[1] = color;
		pp1[0] = color;
		pp1[3] = *pp2;
	}
	while( pp2 != data );
}

static inline void GREY_ALPHA_to_RGBA( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data + size * 2;
	uint8_t  *pp2 = data + size;

	do
	{
		pp1 -= 4;
		pp2 -= 2;

		pp1[2] = pp2[0];
		pp1[1] = pp2[0];
		pp1[0] = pp2[0];
		pp1[3] = pp2[1];
	}
	while ( pp2 != data );
}

static void SwitchPixel(toy::ImageBuffer *image,const uint8_t *data,enum ::toy::Option option)
{
	auto   target = image->_data();
	auto   width  = image->width();
	auto   height = image->height();

	image->_setFormat(option);

	switch ( option )
	{
		case toy::GREY:
			std::memcpy(target,data, width * height);
			GREY_to_RGBA( target, width * height);
			image->_setFormat(toy::RGBA);
			break;

		case toy::GREY_ALPHA:
			std::memcpy(target,data, width * height * 2);
			GREY_ALPHA_to_RGBA( target, width * height * 2);
			image->_setFormat(toy::RGBA);
			break;

		case toy::RGB:
			std::memcpy(target,data, width * height * 3);
			break;

		case toy::RGBA:
			std::memcpy(target,data, width * height * 4);
			break;

		default:
			toy::Oops(TOY_MARK);   // Unknown option.
			image->clean();
	}
}

bool CreateImageBuffer(toy::ImageBuffer *image,const int32_t width,const int32_t height,const uint8_t *data,enum ::toy::Option option)
{
	image->_setWidth(width);
	image->_setHeight(height);

	image->_getAllocator()->size(width * height * 4);

	SwitchPixel(image,data,option);

	return true;
}

toy::ImageBuffer CreateImageBuffer(const int32_t width,const int32_t height,const uint8_t *data,enum ::toy::Option option)
{
	toy::ImageBuffer        result;
	CreateImageBuffer(&result,width,height,data,option);

	return result;
}

}

using namespace toy;

ImageBuffer::ImageBuffer()
{
	;
}

ImageBuffer::~ImageBuffer()
{
	clean();
}

void ImageBuffer::clean()
{
	_allocator.free();
}
