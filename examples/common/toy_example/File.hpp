
#pragma once

#include <toy/File.hpp>
#include <toy/ImageBuffer.hpp>

namespace toy{
namespace example{

inline static bool LoadImage( const std::string& folder,
                              const std::string& file,
                              toy::ImageBuffer*  image,
                              enum toy::File::Mode mode = toy::File::STD)
{
	toy::File       dev(mode);

	dev.openDir(folder);

	if ( ! dev.open(file) )
	{
		toy::Logger << "Image file not find!" << toy::NewLine;
	}
	else if ( ! toy::file::loader::Load(&dev,image) )
	{
		toy::Logger << "Image load failed!" << toy::NewLine;
	}
	else if ( image->data()==nullptr )
	{
		toy::Logger << "Image load nothing!" << toy::NewLine;
	}
	else
	{
		toy::Logger << "Image load success!" << toy::NewLine;
		return true;
	}

	return false;
}

}}
