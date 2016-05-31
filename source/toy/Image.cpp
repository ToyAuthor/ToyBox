#include <cstdlib>
#include <cstring>
#include "toy/Image.hpp"
#include "toy/Math.hpp"


namespace toy{
namespace image{

static inline void GREY_ALPHA_to_RGBA( uint8_t* data, uint32_t size )
{
	uint8_t      *pp1 = data + size*2 - 4;
	uint8_t      *pp2 = data + size   - 2;

	for( ; pp2 != data ; pp1-=4,pp2-=2 )
	{
		pp1[2] = pp2[0];
		pp1[1] = pp2[0];
		pp1[0] = pp2[0];
		pp1[3] = pp2[1];
	}

	// Handle the last pixel.
	pp1[2] = pp2[0];
	pp1[1] = pp2[0];
	pp1[0] = pp2[0];
	pp1[3] = pp2[1];
}

static void SwitchPixel(toy::ImageOpener *image,uint8_t *data,enum Pixel option)
{
	auto   target = static_cast<uint8_t*>(image->getData());
	auto   width  = image->getWidth();
	auto   height = image->getHeight();

	switch ( option )
	{
		case GREY:
			toy::Oops(TOY_MARK);   // Not ready yet.
			image->clean();
			break;

		case GREY_ALPHA:
			std::memcpy(target,data, width * height * 2);
			GREY_ALPHA_to_RGBA( target, width * height * 2);
			break;

		case RGB:
			toy::Oops(TOY_MARK);   // Not ready yet.
			image->clean();
			break;

		case RGBA:
			std::memcpy(target,data, width * height * 4);
			break;

		default:
			toy::Oops(TOY_MARK);   // Unknown option.
			image->clean();
	}
}

toy::Image Create(const int32_t width,const int32_t height,uint8_t *data,enum Pixel option)
{
	toy::Image        result;
	toy::ImageOpener  image(&result);

	image.setWidth(width);
	image.setHeight(height);

	image.getAllocator()->setSize(width * height * 4);

	SwitchPixel(&image,data,option);

	return result;
}

}//namespace image{
}//namespace toy{


using namespace toy;


Image::Image()
{
	;
}

Image::~Image()
{
	clean();
}

void Image::clean()
{
	_data.free();
}

template<typename T>
inline std::shared_ptr<T> MakeArray(int size)
{
	return std::shared_ptr<T>( new T[size], []( T *p ){ delete [] p; } );
}

void Image::upsideDown()
{
	auto        data        = static_cast<uint8_t*>(_data.getData());
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
