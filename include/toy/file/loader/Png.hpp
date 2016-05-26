
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class File;
class Image;

namespace file{
namespace loader{
namespace png{

TOY_API bool Load(File *f,Image *m);
//TOY_API bool Save(std::string filename,Image *map);

}//namespace png
}//namespace loader
}//namespace file
}//namespace toy
