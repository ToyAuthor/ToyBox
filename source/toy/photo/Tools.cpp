#include <cstring>
#include "toy/photo/Tools.hpp"

namespace toy{
namespace photo{

template<typename T>
inline static std::shared_ptr<T> MakeArray(int size)
{
	return std::shared_ptr<T>( new T[size], []( T *p ){ delete [] p; } );
}

static void UpsideDownImage(uint8_t *data,int32_t width,int32_t height,const int color_pixel)
{
	const int   oneline     = width*color_pixel;
	const auto  temp        = MakeArray<uint8_t>(oneline);
	const auto  size        = height*oneline;
	const auto  redraw      = ( (size - (size%2))/2 )- oneline;

	for ( int i=0 ; i<redraw ; i=i+oneline )
	{
		// Swap two line.
		std::memcpy(temp.get(),data+i,oneline);
		std::memcpy(data+i,data+size-i-oneline,oneline);
		std::memcpy(data+size-i-oneline,temp.get(),oneline);
	}
}

static void UpsideDownRGB(uint8_t *data,int32_t width,int32_t height)
{
	UpsideDownImage(data,width,height,3);
}

static void UpsideDownRGBA(uint8_t *data,int32_t width,int32_t height)
{
	UpsideDownImage(data,width,height,4);
}

void UpsideDown(toy::ImageBuffer *image)
{
	switch ( image->format() )
	{
		case toy::RGB:
			UpsideDownRGB(image->_data(),image->width(),image->height());
			break;
		case toy::RGBA:
			UpsideDownRGBA(image->_data(),image->width(),image->height());
			break;
		default:
			toy::Oops(TOY_MARK);
	}
}

}}
