
#pragma once

#include "toy/Standard.hpp"

namespace toy{

class File;
class Image;

namespace file{
namespace loader{
namespace bmp{

TOY_API bool Load(File *f,Image *m);
TOY_API bool Save(File *f,Image *m);   // File mode STD only.

}//namespace bmp
}//namespace loader
}//namespace file
}//namespace toy
