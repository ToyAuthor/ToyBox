
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"

namespace toy{
class File;
class ImageBuffer;
}

namespace toy{
namespace file{
namespace loader{

TOY_API_FILE bool Load(::toy::File *f,::toy::ImageBuffer *m);
TOY_API_FILE bool Save(std::string filename,::toy::ImageBuffer *map);

}}}
