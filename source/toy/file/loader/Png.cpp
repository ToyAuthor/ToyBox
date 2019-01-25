#include <cstdlib>
#include "toy/ImageBuffer.hpp"
#include "toy/file/loader/Png.hpp"
#include "toy/file/loader/Image.hpp"

namespace toy{ namespace file{ namespace loader{
extern bool _SavePng(const std::string&,toy::ImageBuffer *);
}}}

namespace toy{
namespace file{

bool loader::png::Load(toy::File *pIO,toy::ImageBuffer *map)
{
	return loader::Load(pIO,map);
}

bool loader::png::Save(std::string filename,toy::ImageBuffer *map)
{
	return loader::_SavePng(filename,map);
}

}}
