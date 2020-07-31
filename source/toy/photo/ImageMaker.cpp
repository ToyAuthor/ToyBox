#include <cstring>
#include "toy/photo/ImageMaker.hpp"

namespace toy{
namespace photo{

void MakeCircle( toy::ImageBuffer  *image,
                 uint32_t          width,
                 uint32_t          border,
                 const toy::Color& color )
{
	(void)border;

	float r = 255.0f * float(color.red());
	float g = 255.0f * float(color.green());
	float b = 255.0f * float(color.blue());
	float a = 255.0f * float(color.alpha());

	size_t  size = width * width * 4;

	image->_setFormat(toy::RGBA);
	image->_setWidth(width);
	image->_setHeight(width);
	image->_getAllocator()->size(size);

	auto   data = image->_data();
	std::memset(data,0,width * width * 4);

	size_t  radius = width/2;
	size_t  radiusSquare = radius*radius;
	size_t  pixel = 1;

	for ( size_t index=0 ; index<size ; index+=4,pixel++ )
	{
		int  x = ( pixel )%width;
		int  y = ( pixel )/width;
		x = radius-x;
		y = radius-y;
		size_t  xs = x*x;
		size_t  ys = y*y;

		if ( (xs+ys)<=radiusSquare )
		{
			data[ index   ] = r;
			data[ index+1 ] = g;
			data[ index+2 ] = b;
			data[ index+3 ] = a;
		}
	}
}

void MakeRectangle( toy::ImageBuffer  *image,
                    uint32_t          width,
                    uint32_t          height,
                    uint32_t          border,
                    const toy::Color& color )
{
	(void)border;

	float r = 255.0f * float(color.red());
	float g = 255.0f * float(color.green());
	float b = 255.0f * float(color.blue());
	float a = 255.0f * float(color.alpha());

	size_t  size = width * height * 4;

	image->_setFormat(toy::RGBA);
	image->_setWidth(width);
	image->_setHeight(height);
	image->_getAllocator()->size(size);

	auto   data = image->_data();

	for ( size_t index=0 ; index<size ; index+=4 )
	{
		data[ index   ] = r;
		data[ index+1 ] = g;
		data[ index+2 ] = b;
		data[ index+3 ] = a;
	}
}

}}
