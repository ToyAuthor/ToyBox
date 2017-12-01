
#pragma once

#include "toy/Standard.hpp"
#include "toy/Allocator01.hpp"

namespace toy{

// It's a container of image file.
class TOY_API ImageBuffer
{
	public:

		ImageBuffer();
		~ImageBuffer();

		void    clean();

		/*
		 * Give you a memory address of the image data.
		 * Return nullptr if it's a empty object.
		 */
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

		enum ::toy::Option format() const
		{
			return _format;
		}

	private:

		Allocator01          _allocator;      // Saving a image data on memory.
		int32_t              _height = 0;
		int32_t              _width = 0;
		enum ::toy::Option   _format = ::toy::RGBA;

	public:

		uint8_t* _data()
		{
			return (uint8_t*)(_allocator.data());
		}

		void _setHeight(int32_t n)
		{
			_height=n;
		}

		void _setWidth(int32_t n)
		{
			_width=n;
		}

		void _setFormat(enum ::toy::Option fmt)
		{
			_format = fmt;
		}

		Allocator01* _getAllocator()
		{
			return &_allocator;
		}
};

TOY_API extern bool CreateImageBuffer(toy::ImageBuffer *output,const int32_t width,const int32_t height,const uint8_t *data,enum ::toy::Option option = ::toy::RGBA);
TOY_API extern auto CreateImageBuffer(                         const int32_t width,const int32_t height,const uint8_t *data,enum ::toy::Option option = ::toy::RGBA)->toy::ImageBuffer;

}
