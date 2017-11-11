#include <cstdlib>
#include "toy/file/loader/Png.hpp"
#include "toy/file/loader/Image.hpp"



namespace toy{
namespace file{

bool loader::png::Load(toy::File *pIO,toy::ImageBuffer *map)
{
	return loader::Load(pIO,map);
}
/*
bool loader::png::Save(std::string filename,toy::ImageBuffer *map)
{
	return loader::Save(filename,map);
}
*/
}//namespace file
}//namespace toy
