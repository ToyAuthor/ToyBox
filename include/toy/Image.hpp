
#pragma once

#include "toy/Standard.hpp"
#include "toy/Allocator01.hpp"


namespace toy{

class ImageOpener;


// It's a container of image file.
class TOY_API Image
{
	public:
		friend class toy::ImageOpener;

		Image();
		~Image();

		void    clean();
		void    upsideDown();

		// Give you a memory address of the image data. Return nullptr if it's a empty object.
		const uint8_t* data() const
		{
			return (uint8_t*)(_allocator.data());
		}

		int32_t height() const
		{
			return _height;
		}

		int32_t width() const
		{
			return _width;
		}

		int32_t size() const
		{
			return _width * _height;
		}

	private:

		Allocator01     _allocator;      // Saving a image data on memory.
		int32_t         _height = 0;
		int32_t         _width = 0;

	public:

		uint8_t* _data() const
		{
			return (uint8_t*)(_allocator.data());
		}

};

// You can use it to modify the inside of Image.
class ImageOpener
{
	public:

		ImageOpener(Image *core):_core(core)
		{
			;
		}

		~ImageOpener(){}

		void clean()
		{
			_core->clean();
		}

		Allocator01* allocator()
		{
			return &(_core->_allocator);
		}

		uint8_t* data() const
		{
			return _core->_data();
		}

		int32_t height() const
		{
			return _core->_height;
		}

		int32_t width() const
		{
			return _core->_width;
		}

		int32_t size() const
		{
			return _core->size();
		}

		void size(size_t n)
		{
			_core->_allocator.size(n);
		}

		void height(int32_t n)
		{
			_core->_height=n;
		}

		void width(int32_t n)
		{
			_core->_width=n;
		}

	private:

		Image   *_core;
};

namespace image{

enum Pixel
{
	GREY = 1,
	GREY_ALPHA,
	RGB,
	RGBA,
};

TOY_API extern bool       Create(toy::Image *output,const int32_t width,const int32_t height,const uint8_t *data,enum Pixel option = RGBA);
TOY_API extern toy::Image Create(                   const int32_t width,const int32_t height,const uint8_t *data,enum Pixel option = RGBA);

}//namespace image{

}//namespace toy
