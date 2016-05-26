#include <cstdlib>
#include "toy/file/loader/Png.hpp"
#include "toy/file/loader/Image.hpp"

//#define PNG_DEBUG 3
//#include <png.h>


namespace toy{
namespace file{

bool loader::png::Load(File *pIO,Image *map)
{
	return loader::Load(pIO,map);
}
/*
bool loader::png::Save(std::string filename,Image *map)
{
	return loader::Save(filename,map);
}
*/
}//namespace file
}//namespace toy
