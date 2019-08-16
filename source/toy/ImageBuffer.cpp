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

		pp1[3] = *pp2;
		pp1[2] = color;
		pp1[1] = color;
		pp1[0] = color;
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

		pp1[3] = pp2[1];
		pp1[2] = pp2[0];
		pp1[1] = pp2[0];
		pp1[0] = pp2[0];
	}
	while ( pp2 != data );
}

static inline void RGB_to_RGBA( uint8_t* data, uint32_t size )
{
	uint32_t   nsize = size/3;

	if ( (nsize*3)!=size )
	{
		toy::Oops(TOY_MARK);
	}

	uint8_t  *pp1 = data + size + nsize;
	uint8_t  *pp2 = data + size;

	do
	{
		pp1 -= 4;
		pp2 -= 3;

		pp1[3] = 255;
		pp1[2] = pp2[2];
		pp1[1] = pp2[1];
		pp1[0] = pp2[0];
	}
	while ( pp2 != data );
}

bool ImageBuffer::toRGBA()
{
	if ( _format== toy::RGBA)
	{
		return true;
	}

	auto  mapSize = _width * _height;

	_allocator.size( mapSize * 4 );

	switch( _format )
	{
		case toy::RGB:
			RGB_to_RGBA( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::GREY:
			GREY_to_RGBA( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::GREY_ALPHA:
			GREY_ALPHA_to_RGBA( (uint8_t*)(_allocator.data()), mapSize);
			break;

		default:
			toy::Oops(TOY_MARK);
			return false;
	}

	_format = toy::RGBA;

	return true;
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
			image->_setFormat(toy::GREY);
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

bool CreateImageBuffer(toy::ImageBuffer *image,const uint32_t width,const uint32_t height,const uint8_t *data,enum ::toy::Option option)
{
	image->_setWidth(width);
	image->_setHeight(height);

	image->_getAllocator()->size(width * height * 4);

	SwitchPixel(image,data,option);

	return true;
}

toy::ImageBuffer CreateImageBuffer(const uint32_t width,const uint32_t height,const uint8_t *data,enum ::toy::Option option)
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

static inline uint8_t BlendColor(uint8_t ac,uint8_t bc,uint8_t aa,uint8_t ba)
{
	float  colorA = ac;
	float  colorB = bc;
	float  alphaA = aa;
	float  alphaB = ba;

	colorA /= 255.0f;
	colorB /= 255.0f;
	alphaA /= 255.0f;
	alphaB /= 255.0f;

	float  res = colorA * alphaA + colorB * alphaB;

	if ( res>255.0f )
	{
		res = 255.0f;
	}

	uint8_t   result = res;

	return result;
}

static inline uint8_t BlendAlpha(uint8_t a,uint8_t b)
{
	uint32_t result = a;
	result += b;

	if ( result>255 )
	{
		return 255;
	}

	return result;
}

ImageBuffer& ImageBuffer::operator +=(const ImageBuffer& model)
{
	if ( (_format!=toy::RGBA) ||
	     (model.format()!=toy::RGBA) ||
	     (this->size()!=model.size()) )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	auto    data = model.data();
	size_t  size = model.size();
	auto    mydata = this->_data();

	for ( size_t index=0 ; index<size ; index+=4 )
	{
		uint8_t  alphaA = mydata[ index+3 ];
		uint8_t  alphaB = data[ index+3 ];

		mydata[ index   ] = BlendColor( mydata[index  ], data[index  ], alphaA, alphaB );
		mydata[ index+1 ] = BlendColor( mydata[index+1], data[index+1], alphaA, alphaB );
		mydata[ index+2 ] = BlendColor( mydata[index+2], data[index+2], alphaA, alphaB );
		mydata[ index+3 ] = BlendAlpha(alphaA,alphaB);
	}

	return *this;
}
