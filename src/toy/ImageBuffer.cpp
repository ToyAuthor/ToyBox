#include <cstdlib>
#include <cstring>
#include "toy/ImageBuffer.hpp"
#include "toy/Math.hpp"

namespace toy{

static inline void GREY_ALPHA_to_GREY( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data;
	uint8_t  *pp2 = data;

	const uint8_t  *end = data + (size*2);

	do
	{
		pp1[0] = pp2[0];

		pp1 += 1;
		pp2 += 2;
	}
	while( pp2 != end );
}

static inline void RGB_to_GREY( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data;
	uint8_t  *pp2 = data;

	const uint8_t  *end = data + (size*3);

	do
	{
//		pp1[0] = uint8_t( (float(pp2[0])+float(pp2[1])+float(pp2[2]))/3 );
		pp1[0] = uint8_t(( uint_fast16_t(pp2[0])*38+uint_fast16_t(pp2[1])*75+uint_fast16_t(pp2[2])*15 )>>7);
//		pp1[0] = uint8_t(( uint_fast16_t(pp2[0])+uint_fast16_t(pp2[1])<<1+uint_fast16_t(pp2[2]) )>>1);

		pp1 += 1;
		pp2 += 3;
	}
	while( pp2 != end );
}

static inline void RGBA_to_GREY( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data;
	uint8_t  *pp2 = data;

	const uint8_t  *end = data + (size<<2);

	do
	{
//		pp1[0] = uint8_t( (float(pp2[0])+float(pp2[1])+float(pp2[2]))/3 );
		pp1[0] = uint8_t(( uint_fast16_t(pp2[0])*38+uint_fast16_t(pp2[1])*75+uint_fast16_t(pp2[2])*15 )>>7);
//		pp1[0] = uint8_t(( uint_fast16_t(pp2[0])+uint_fast16_t(pp2[1])<<1+uint_fast16_t(pp2[2]) )>>1);

		pp1 += 1;
		pp2 += 4;
	}
	while( pp2 != end );
}

static inline void GREY_to_GREY_ALPHA( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data + size * 2;
	uint8_t  *pp2 = data + size;

	do
	{
		pp1 -= 2;
		pp2 -= 1;

		pp1[1] = 255;
		pp1[0] = pp2[0];
	}
	while( pp2 != data );
}

static inline void RGB_to_GREY_ALPHA( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data;
	uint8_t  *pp2 = data;

	const uint8_t  *end = data + (size*3);

	do
	{
		pp1[0] = uint8_t( (float(pp2[0])+float(pp2[1])+float(pp2[2]))/3 );
		pp1[1] = 255;

		pp1 += 2;
		pp2 += 3;
	}
	while( pp2 != end );
}

static inline void RGBA_to_GREY_ALPHA( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data;
	uint8_t  *pp2 = data;

	const uint8_t  *end = data + (size<<2);

	do
	{
		pp1[0] = uint8_t( (float(pp2[0])+float(pp2[1])+float(pp2[2]))/3 );
		pp1[1] = pp2[3];

		pp1 += 2;
		pp2 += 4;
	}
	while( pp2 != end );
}

static inline void GREY_to_RGB( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data + size * 3;
	uint8_t  *pp2 = data + size;

	do
	{
		pp1 -= 3;
		pp2 -= 1;

		pp1[2] = pp2[0];
		pp1[1] = pp2[0];
		pp1[0] = pp2[0];
	}
	while( pp2 != data );
}

static inline void GREY_ALPHA_to_RGB( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data + size * 3;
	uint8_t  *pp2 = data + size * 2;

	do
	{
		pp1 -= 3;
		pp2 -= 2;

		pp1[2] = pp2[0];
		pp1[1] = pp2[0];
		pp1[0] = pp2[0];
	}
	while ( pp2 != data );
}

static inline void RGBA_to_RGB( uint8_t* data, uint32_t size )
{
	uint8_t  *pp1 = data;
	uint8_t  *pp2 = data;

	const uint8_t  *end = data + (size<<2);

	do
	{
		pp1[0] = pp2[0];
		pp1[1] = pp2[1];
		pp1[2] = pp2[2];

		pp1 += 3;
		pp2 += 4;
	}
	while ( pp2 != end );
}

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
	uint8_t  *pp1 = data + size * 4;
	uint8_t  *pp2 = data + size * 2;

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
	uint8_t  *pp1 = data + size * 4;
	uint8_t  *pp2 = data + size * 3;

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

bool ImageBuffer::toGREY()
{
	if ( _format== toy::GREY)
	{
		return true;
	}

	auto  mapSize = _width * _height;

	_allocator.size( mapSize );

	switch( _format )
	{
		case toy::RGBA:
			RGBA_to_GREY( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::RGB:
			RGB_to_GREY( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::GREY_ALPHA:
			GREY_ALPHA_to_GREY( (uint8_t*)(_allocator.data()), mapSize);
			break;

		default:
			toy::Oops(TOY_MARK);
			return false;
	}

	_format = toy::GREY;

	return true;
}

bool ImageBuffer::toGREY_ALPHA()
{
	if ( _format== toy::GREY_ALPHA)
	{
		return true;
	}

	auto  mapSize = _width * _height;

	_allocator.size( mapSize * 2 );

	switch( _format )
	{
		case toy::RGBA:
			RGBA_to_GREY_ALPHA( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::RGB:
			RGB_to_GREY_ALPHA( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::GREY:
			GREY_to_GREY_ALPHA( (uint8_t*)(_allocator.data()), mapSize);
			break;

		default:
			toy::Oops(TOY_MARK);
			return false;
	}

	_format = toy::RGBA;

	return true;
}

bool ImageBuffer::toRGB()
{
	if ( _format== toy::RGB)
	{
		return true;
	}

	auto  mapSize = _width * _height;

	_allocator.size( mapSize * 3 );

	switch( _format )
	{
		case toy::RGBA:
			RGBA_to_RGB( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::GREY:
			GREY_to_RGB( (uint8_t*)(_allocator.data()), mapSize);
			break;

		case toy::GREY_ALPHA:
			GREY_ALPHA_to_RGB( (uint8_t*)(_allocator.data()), mapSize);
			break;

		default:
			toy::Oops(TOY_MARK);
			return false;
	}

	_format = toy::RGBA;

	return true;
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
			break;

		case toy::GREY_ALPHA:
			std::memcpy(target,data, width * height * 2);
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
	if ( false==image->_getAllocator()->size(width * height * 4) )
	{
		return false;
	}

	image->_setWidth(width);
	image->_setHeight(height);

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

	return static_cast<uint8_t>(res);
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
