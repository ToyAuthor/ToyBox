
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"


namespace toy{

class File;
class Image;

namespace file{
namespace loader{

TOY_API_FILE bool Load(File *f,Image *m);
TOY_API_FILE bool Save(std::string filename,Image *map);

}//namespace loader
}//namespace file
}//namespace toy
