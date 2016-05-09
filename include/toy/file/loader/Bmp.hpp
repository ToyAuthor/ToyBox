
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class File;
class Image;

namespace file{
namespace loader{

class TOY_API Bmp
{
	public:

		Bmp(){}
		~Bmp(){}

	static bool    Load(File *f,Image *m);
	static bool    Save(File *f,Image *m);   // Saving BMP file. File mode STD only.
};

}//namespace loader
}//namespace file
}//namespace toy
