#include <cstdlib>
#include <cstring>
#include "toy/Image.hpp"
#include "toy/file/File.hpp"
#include "toy/file/loader/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "toy/file/loader/stb/stb_image.h"


namespace toy{
namespace file{


static int ReadImage(void *user,char *data,int size)
{
	auto   dev = static_cast<File*>(user);
	dev->read(data,size);

	return size;
}

static void SkipImage(void *user,int n)
{
	auto   dev = static_cast<File*>(user);

	dev->seek(File::CUR,n);
}

static int EndOfFile(void *user)
{
	auto   dev = static_cast<File*>(user);

	return dev->isEnd();
}

bool loader::Load(File *f,Image *map)
{
	auto   io = static_cast<void*>(f);
	ImageOpener  image(map);

	int32_t      width  = 0;
	int32_t      height = 0;
	int32_t      pixel = 0;

	stbi_io_callbacks    callback;

	callback.eof = EndOfFile;
	callback.read = ReadImage;
	callback.skip = SkipImage;

	auto   data = stbi_load_from_callbacks( &callback, io, &width, &height, &pixel, STBI_rgb_alpha );

	image.setHeight(height);
	image.setWidth(width);
	image.getAllocator()->setSize(width*height*pixel);

	std::memcpy( image.getData(), data, width*height*pixel );

	stbi_image_free(data);

	return 1;
}

}//namespace file
}//namespace toy
