#include "toy/ImageBuffer.hpp"
#include "toy/file/File.hpp"
#include "toy/file/loader/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "toy/file/loader/stb/stb_image.h"
#include "toy/file/loader/stb/stb_image_write.h"


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

	int32_t      width  = 0;
	int32_t      height = 0;
	int32_t      pixel  = 0;

	stbi_io_callbacks    callback;

	callback.read = ReadImage;
	callback.skip = SkipImage;
	callback.eof  = EndOfFile;

	stbi_set_flip_vertically_on_load(1);    //upside down

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

bool loader::Save(std::string filename,toy::ImageBuffer *map)
{
	stbi_write_tga(filename.c_str(), map->width(), map->height(), 4, map->data());
	return 1;
}

}//namespace file
}//namespace toy

#undef STB_IMAGE_IMPLEMENTATION
#undef STB_IMAGE_WRITE_IMPLEMENTATION
