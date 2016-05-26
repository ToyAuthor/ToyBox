
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

		// Give you a memory address about the image data. Return nullptr if it's a empty object.
		uint8_t* getData() const
		{
			return (uint8_t*)(_data.getData());
		}

		int32_t getHeight() const
		{
			return _height;
		}

		int32_t getWidth() const
		{
			return _width;
		}

		int32_t getSize() const
		{
			return _width * _height;
		}

	private:

		Allocator01     _data;      // Saving a image data on memory.
		int32_t         _height = 0;
		int32_t         _width = 0;

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

		Allocator01* getAllocator()
		{
			return &(_core->_data);
		}

		uint8_t* getData() const
		{
			return _core->getData();
		}

		int32_t getHeight() const
		{
			return _core->_height;
		}

		int32_t getWidth() const
		{
			return _core->_width;
		}

		int32_t getSize() const
		{
			return _core->getSize();
		}

		void setSize(size_t n)
		{
			_core->_data.setSize(n);
		}

		void setHeight(int32_t n)
		{
			_core->_height=n;
		}

		void setWidth(int32_t n)
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

TOY_API toy::Image Create(const int32_t width,const int32_t height,uint8_t *data,enum Pixel option = RGBA);

}//namespace image{

}//namespace toy
