
#pragma once

#include "toy/Standard.hpp"
#include "toy/memory/Manager02.hpp"

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

		uint32_t height() const
		{
			return _height;
		}

		uint32_t width() const
		{
			return _width;
		}

		uint32_t size() const
		{
			return _width * _height;
		}

		enum ::toy::Option format() const
		{
			return _format;
		}

		ImageBuffer& operator +=(const ImageBuffer& model);

	private:

		toy::memory::Manager02    _allocator;      // Saving a image data on memory.
		uint32_t                  _height = 0;
		uint32_t                  _width  = 0;
		enum ::toy::Option        _format = ::toy::RGBA;

	public:

		uint8_t* _data()
		{
			return (uint8_t*)(_allocator.data());
		}

		void _setHeight(uint32_t n)
		{
			_height=n;
		}

		void _setWidth(uint32_t n)
		{
			_width=n;
		}

		void _setFormat(enum ::toy::Option fmt)
		{
			_format = fmt;
		}

		auto _getAllocator()->toy::memory::Manager02*
		{
			return &_allocator;
		}
};

TOY_API extern bool CreateImageBuffer(toy::ImageBuffer *output,const uint32_t width,const uint32_t height,const uint8_t *data,enum ::toy::Option option = ::toy::RGBA);
TOY_API extern auto CreateImageBuffer(                         const uint32_t width,const uint32_t height,const uint8_t *data,enum ::toy::Option option = ::toy::RGBA)->toy::ImageBuffer;

}
