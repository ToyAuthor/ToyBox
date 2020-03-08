#include <cstring>
#include "toy/Math.hpp"
#include "toy/photo/Tools.hpp"

namespace toy{
namespace photo{

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

static void GeryToRGBA(const uint8_t *input,uint8_t *output,uint32_t pixel,const toy::Color &color)
{
	uint8_t  *pp1 = output + pixel * 4;
	const uint8_t  *pp2 = input + pixel;
	uint8_t  colorR = color.red();
	uint8_t  colorG = color.green();
	uint8_t  colorB = color.blue();
	float    colorA = color.alpha();

	do
	{
		pp1 -= 4;
		pp2 -= 1;

		pp1[3] = (*pp2) * colorA;
		pp1[2] = colorB;
		pp1[1] = colorG;
		pp1[0] = colorR;
	}
	while( pp2 != input );
}

void ToRGBA001(toy::ImageBuffer *image)
{
	ToRGBA001(image,toy::Color(float(1.0),float(0.0),float(1.0),float(1.0)));
}

void ToRGBA001(toy::ImageBuffer *image,const toy::Color &color)
{
	if ( image->format()==toy::RGBA )
	{
		return;
	}

	if ( image->format()!=toy::GREY )
	{
		throw toy::Exception(TOY_MARK);
	}

	auto pixel = image->size();
	image->_getAllocator()->size( pixel * 4 );
	GeryToRGBA(image->data(),image->_data(),pixel,color);
	image->_setFormat(toy::RGBA);
}

void ToRGBA001(const toy::ImageBuffer &input,toy::ImageBuffer *output)
{
	ToRGBA001(input,output,toy::Color(float(1.0),float(0.0),float(1.0),float(1.0)));
}

void ToRGBA001(const toy::ImageBuffer &input,toy::ImageBuffer *output,const toy::Color &color)
{
	if ( input.format()==toy::RGBA )
	{
		return;
	}

	if ( input.format()!=toy::GREY )
	{
		throw toy::Exception(TOY_MARK);
	}

	auto pixel = input.size();
	output->_getAllocator()->size( pixel * 4 );
	GeryToRGBA(input.data(),output->_data(),pixel,color);
	output->_setFormat(toy::RGBA);
	output->_setWidth(input.width());
	output->_setHeight(input.height());
}

//------------------------------------------------------------------------------

static void ExtensionSize(toy::ImageBuffer *image,int pixel,uint32_t newWidth, uint32_t newHeight)
{
	auto  oldWidth  = image->width();
	auto  oldHeight = image->height();

	image->_getAllocator()->size(newWidth*newHeight*pixel);
	image->_setWidth(newWidth);
	image->_setHeight(newHeight);

	uint8_t  *data = image->_data();

	if ( newWidth!=oldWidth )
	{
		uint8_t  *data01 = data + ((newWidth*(oldHeight-1))*pixel);
		uint8_t  *data02 = data + ((oldWidth*(oldHeight-1))*pixel);

		for ( auto j = oldHeight; j>0 ;--j )
		{
			for ( auto i = oldWidth*pixel; i>0 ;--i )
			{
				data01[i-1] = data02[i-1];
			}

			data01 -= newWidth*pixel;
			data02 -= oldWidth*pixel;
		}
	}
}

static void BaseOnTwo(int pixel,toy::ImageBuffer *image)
{
	ExtensionSize( image, pixel, toy::math::Exp1(image->width()),
	                             toy::math::Exp1(image->height()) );
}

void BaseOnTwo(toy::ImageBuffer *image)
{
	switch( image->format() )
	{
		case toy::RGBA:       BaseOnTwo(4,image); break;
		case toy::GREY:       BaseOnTwo(1,image); break;
		case toy::RGB:        BaseOnTwo(3,image); break;
		case toy::GREY_ALPHA: BaseOnTwo(2,image); break;
		default:
			throw toy::Exception(TOY_MARK);
	}
}

//------------------------------------------------------------------------------

}}
