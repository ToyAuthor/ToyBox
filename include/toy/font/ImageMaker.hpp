
#pragma once

#include <string>
#include <cstdint>
#include "toy/ImageBuffer.hpp"
#include "toy/font/Export.hpp"
#include "toy/font/Information.hpp"

namespace toy{
namespace font{

struct ImageMakerPrivate;

// Basically, toy::font::ImageMaker is a wrapper of FreeType2.
class TOY_API_FONT ImageMaker
{
	public:

		ImageMaker();
		ImageMaker(std::string fontLibName);
		~ImageMaker();

		bool open(std::string fontLibName);
		bool open(uint8_t* data, size_t size);
		void close();
		bool empty();
		void setSize(int size);
		auto getHalfwidth()->float;    // The width of a halfwidth character.
		auto getFullwidth()->float;    // The width of a fullwidth character.
		void getImage(toy::ImageBuffer *map,char    ch, ::toy::font::Information *info = nullptr);
		void getImage(toy::ImageBuffer *map,wchar_t ch, ::toy::font::Information *info = nullptr);

	private:

		std::unique_ptr<ImageMakerPrivate>  _this;
};

}}
