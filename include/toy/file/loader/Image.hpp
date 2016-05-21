
#pragma once

#include "toy/Standard.hpp"



namespace toy{

class File;
class Image;

namespace file{
namespace loader{

TOY_API bool Load(File *f,Image *m);


}//namespace loader
}//namespace file
}//namespace toy
