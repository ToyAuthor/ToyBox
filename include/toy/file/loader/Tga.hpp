
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"

namespace toy{

class File;
class ImageBuffer;

namespace file{
namespace loader{
namespace tga{

TOY_API_FILE bool Load(File *f,ImageBuffer *m);    // Not support length encoding.
TOY_API_FILE bool Save(File *f,ImageBuffer *m);    // File mode STD only.

}//namespace tga
}//namespace loader
}//namespace file
}//namespace toy
