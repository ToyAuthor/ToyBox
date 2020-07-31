#include <cstring>
#include "toy/photo/Tools.hpp"

namespace toy{
namespace photo{

static void UpsideDownImage(uint8_t *data,int32_t width,int32_t height,const int color_pixel)
{
	const int   oneline     = width*color_pixel;
	std::vector<uint8_t>    temp(oneline);
	const auto  size        = height*oneline;
	const auto  redraw      = ( (size - (size%2))/2 )- oneline;

	for ( int i=0 ; i<=redraw ; i=i+oneline )
	{
		// Swap two line.
		std::memcpy(temp.data(),data+i,oneline);
		std::memcpy(data+i,data+size-i-oneline,oneline);
		std::memcpy(data+size-i-oneline,temp.data(),oneline);
	}
}

static inline void UpsideDownGREY(toy::ImageBuffer *image)
{
	UpsideDownImage(image->_data(),image->width(),image->height(),1);
}

static inline void UpsideDownGREY_ALPHA(toy::ImageBuffer *image)
{
	UpsideDownImage(image->_data(),image->width(),image->height(),2);
}

static inline void UpsideDownRGB(toy::ImageBuffer *image)
{
	UpsideDownImage(image->_data(),image->width(),image->height(),3);
}

static inline void UpsideDownRGBA(toy::ImageBuffer *image)
{
	UpsideDownImage(image->_data(),image->width(),image->height(),4);
}

static void UpsideDown(toy::ImageBuffer *image)
{
	switch ( image->format() )
	{
		case toy::RGB:
			UpsideDownRGB(image);
			break;
		case toy::RGBA:
			UpsideDownRGBA(image);
			break;
		case toy::GREY:
			UpsideDownGREY(image);
			break;
		case toy::GREY_ALPHA:
			UpsideDownGREY_ALPHA(image);
			break;
		default:
			throw toy::Exception(TOY_MARK);
	}
}

void Flip(toy::ImageBuffer *image,enum toy::Option option)
{
	if ( option==toy::VERTICAL )
	{
		UpsideDown(image);
	}
	else
	{
		toy::Oops(TOY_MARK);
	}
}

void Flip(const toy::ImageBuffer &input,toy::ImageBuffer *output,enum toy::Option option)
{
	*output = input;

	if ( option==toy::VERTICAL )
	{
		UpsideDown(output);
	}
	else
	{
		toy::Oops(TOY_MARK);
	}
}

}}
