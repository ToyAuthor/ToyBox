#include <cstdlib>
#include <cstring>
#include "toy/ImageBuffer.hpp"
#include "toy/Math.hpp"


namespace toy{
namespace image{

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

bool Create(toy::ImageBuffer *image,const int32_t width,const int32_t height,const uint8_t *data,enum ::toy::Option option)
{
	image->_setWidth(width);
	image->_setHeight(height);

	image->_getAllocator()->size(width * height * 4);

	SwitchPixel(image,data,option);

	return true;
}

toy::ImageBuffer Create(const int32_t width,const int32_t height,const uint8_t *data,enum ::toy::Option option)
{
	toy::ImageBuffer        result;
	Create(&result,width,height,data,option);

	return result;
}

}//namespace image{
}//namespace toy{


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

template<typename T>
inline static std::shared_ptr<T> MakeArray(int size)
{
	return std::shared_ptr<T>( new T[size], []( T *p ){ delete [] p; } );
}

void ImageBuffer::upsideDown()
{
	auto        data        = static_cast<uint8_t*>(_allocator.data());
	const int   color_pixel = 4;
	const int   oneline     = _width*color_pixel;
	const auto  temp        = MakeArray<uint8_t>(oneline);
	const auto  size        = _height*oneline;
	const auto  redraw      = ( (size - (size%2))/2 )- _width-1;

	for ( int i=0 ; i<redraw ; i=i+oneline )
	{
		// Swap two line.
		std::memcpy(temp.get(),data+i,oneline);        // temp = top
		std::memcpy(data+i,data+(size-i),oneline);     // top = bottom
		std::memcpy(data+(size-i),temp.get(),oneline); // bottom = temp
	}
}
