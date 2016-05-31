
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class File;
class Image;

namespace file{
namespace loader{
namespace tga{

TOY_API bool Load(File *f,Image *m);    // Not support length encoding.
TOY_API bool Save(File *f,Image *m);    // File mode STD only.

}//namespace tga
}//namespace loader
}//namespace file
}//namespace toy
