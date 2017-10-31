
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"

namespace toy{

class File;
class ImageBuffer;

namespace file{
namespace loader{
namespace png{

TOY_API_FILE bool Load(File *f,ImageBuffer *m);
//TOY_API_FILE bool Save(std::string filename,Image *map);

}//namespace png
}//namespace loader
}//namespace file
}//namespace toy
