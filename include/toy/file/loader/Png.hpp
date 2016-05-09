
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class File;
class Image;

namespace file{
namespace loader{

class TOY_API Png
{
	public:

		Png(){}
		~Png(){}

	static bool    Load(File *f,Image *m);
};

}//namespace loader
}//namespace file
}//namespace toy
