
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
namespace tga{

TOY_API_FILE bool Load(::toy::File *f,::toy::ImageBuffer *m);    // Not support length encoding.
TOY_API_FILE bool Save(::toy::File *f,::toy::ImageBuffer *m);    // File mode STD only.

}}}}
