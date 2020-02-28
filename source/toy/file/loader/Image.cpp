#include "toy/ImageBuffer.hpp"
#include "toy/file/File.hpp"
#include "toy/file/loader/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "toy/file/loader/stb/stb_image.h"
#undef  STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "toy/file/loader/stb/stb_image_write.h"
#undef  STB_IMAGE_WRITE_IMPLEMENTATION

namespace toy{
namespace file{

static int ReadImage(void *user,char *data,int size)
{
	auto   dev = static_cast<toy::File*>(user);

	return dev->read(data,size);
}

static void SkipImage(void *user,int n)
{
	auto   dev = static_cast<toy::File*>(user);

	dev->seek(SEEK_CUR,n);
}

static int EndOfFile(void *user)
{
	auto   dev = static_cast<toy::File*>(user);

	return dev->isEnd();
}

bool loader::Load(toy::File *f,toy::ImageBuffer *map)
{
	auto   io = static_cast<void*>(f);

	int      width  = 0;
	int      height = 0;
	int      pixel  = 0;

	stbi_io_callbacks    callback;

	callback.read = ReadImage;
	callback.skip = SkipImage;
	callback.eof  = EndOfFile;

//	stbi_set_flip_vertically_on_load(1);    //upside down

	auto   data = stbi_load_from_callbacks( &callback, io, &width, &height, &pixel, STBI_default );

	enum toy::Option   fmt = toy::RGBA;

	switch (pixel)
	{
		case 4:
			fmt = toy::RGBA;
			break;
		case 3:
			fmt = toy::RGB;
			break;
		default:
			toy::Oops(TOY_MARK);
			stbi_image_free(data);
			return false;
	}

	if ( ! toy::CreateImageBuffer(map,width,height,data,fmt) )
	{
		toy::Oops(TOY_MARK);
		stbi_image_free(data);
		return false;
	}

	stbi_image_free(data);

	return true;
}

bool loader::Save(const std::string &filename,toy::ImageBuffer *map)
{
	int   width  = map->width();
	int   height = map->height();

	if ( static_cast<uint32_t>( width)!=map->width()  ) return false;
	if ( static_cast<uint32_t>(height)!=map->height() ) return false;

	int fmt = 4;

	if ( map->format()==toy::RGB )
	{
		fmt = 3;
	}

	if ( stbi_write_png(filename.c_str(), width, height, fmt, map->data(), 0)==1 )
	{
		return true;
	}

	return false;
}

namespace loader{
bool _SavePng(const std::string &filename,toy::ImageBuffer *map)
{
	return loader::Save(filename,map);
}
}

}//namespace file
}//namespace toy
