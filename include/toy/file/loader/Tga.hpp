
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class File;
class Image;

namespace file{
namespace loader{

class TOY_API Tga
{
	public:

		Tga(){}
		~Tga(){}

	static bool    Load(File *f,Image *m); ///< Loading TGA file. No Run Length Encoding.
	static bool    Save(File *f,Image *m); ///< Saving TGA file. File mode STD only.
};

}//namespace loader
}//namespace file
}//namespace toy
