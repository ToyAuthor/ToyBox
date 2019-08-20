#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include "toy/font/ImageMaker.hpp"

namespace toy{
namespace font{
struct ImageMakerPrivate
{
	FT_Library    library = nullptr;
	FT_Face       face = nullptr;
	int           spaceWidth = 0;
	int           fullwidthSpaceWidth = 0;
};
}}

using namespace toy;
using namespace font;

ImageMaker::ImageMaker():_this(new ::toy::font::ImageMakerPrivate)
{
	;
}

ImageMaker::ImageMaker(std::string fontLibName):_this(new ::toy::font::ImageMakerPrivate)
{
	if ( ! open(fontLibName) )
	{
		throw toy::Exception(TOY_MARK);
	}
}

ImageMaker::~ImageMaker()
{
	close();
}

bool ImageMaker::empty()
{
	if ( _this->library )
	{
		return false;
	}

	return true;
}

bool ImageMaker::open(std::string fontLibName)
{
	close();

	if ( FT_Init_FreeType(&(_this->library)) )
	{
		return false;
	}

	if ( FT_New_Face(_this->library, fontLibName.c_str(), 0, &(_this->face)) )
	{
		return false;
	}

	FT_Select_Charmap(_this->face, FT_ENCODING_UNICODE);

	this->setSize(16);

	return true;
}

bool ImageMaker::open(uint8_t* data, size_t size)
{
	close();

	if ( FT_Init_FreeType(&(_this->library)) )
	{
		return false;
	}

	if ( FT_New_Memory_Face(_this->library,data,size,0,&(_this->face) ) )
	{
		return false;
	}

	FT_Select_Charmap(_this->face, FT_ENCODING_UNICODE);

	return true;
}

void ImageMaker::close()
{
	if ( _this->face )
	{
		FT_Done_Face( _this->face );
		_this->face = nullptr;
	}

	if ( _this->library )
	{
		FT_Done_FreeType( _this->library );
		_this->library = nullptr;
	}

	_this->spaceWidth = 0;
}

void ImageMaker::setSize(int size)
{
	if ( _this->face->size->metrics.x_ppem != size)
	{
		auto  result = FT_Set_Pixel_Sizes(_this->face, 0, size);

		if ( result == FT_Err_Invalid_Pixel_Size )
		{
			if ( ! FT_IS_SCALABLE(_this->face))
			{
				toy::Oops(TOY_MARK);
			}
		}

		if ( result != FT_Err_Ok )
		{
			toy::Oops(TOY_MARK);
		}
	}
}

void ImageMaker::getImage(toy::ImageBuffer *map,char ch, ::toy::font::Information *info)
{
	std::string   str(1,ch);

	auto   wstr = toy::utf::UTF8ToWChar(str);

	this->getImage(map,wstr[0],info);
}

void ImageMaker::getImage(toy::ImageBuffer *map,wchar_t ch, ::toy::font::Information *info)
{
	FT_Load_Char(_this->face, ch, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT);

	FT_Glyph     glyph;

	FT_Get_Glyph( _this->face->glyph, &glyph );

	FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );

	auto    bitmap = &( reinterpret_cast<FT_BitmapGlyph>(glyph)->bitmap );

	if ( bitmap->width==0 || bitmap->rows==0 )
	{
		map->clean();
	}
	else
	{
		toy::CreateImageBuffer( map,
		                        bitmap->width,
		                        bitmap->rows,
		                        bitmap->buffer,
		                        toy::GREY );
	}

	if ( info )
	{
		info->metrics.width        = _this->face->glyph->metrics.width;
		info->metrics.height       = _this->face->glyph->metrics.height;
		info->metrics.horiBearingX = _this->face->glyph->metrics.horiBearingX;
		info->metrics.horiBearingY = _this->face->glyph->metrics.horiBearingY;
		info->metrics.horiAdvance  = _this->face->glyph->metrics.horiAdvance;
		info->metrics.vertBearingX = _this->face->glyph->metrics.vertBearingX;
		info->metrics.vertBearingY = _this->face->glyph->metrics.vertBearingY;
		info->metrics.vertAdvance  = _this->face->glyph->metrics.vertAdvance;
	}

	FT_Done_Glyph(glyph);
}

float ImageMaker::getHalfwidth()
{
	if ( _this->spaceWidth == 0 )
	{
		toy::ImageBuffer        buffer;
		toy::font::Information  info;

		getImage(&buffer,L'_',&info);

		float   w = buffer.width();

		_this->spaceWidth = (w * info.metrics.horiBearingX / info.metrics.width) + w;
	}

	return _this->spaceWidth;
}

float ImageMaker::getFullwidth()
{
	if ( _this->fullwidthSpaceWidth == 0 )
	{
		toy::ImageBuffer        buffer;
		toy::font::Information  info;

		getImage(&buffer,wchar_t(0x203B),&info);

		float   w = buffer.width();

		_this->fullwidthSpaceWidth = (w * info.metrics.horiBearingX / info.metrics.width) + w;
	}

	return _this->fullwidthSpaceWidth;
}
