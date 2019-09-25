
#pragma once

#include "toy/webp/Export.hpp"

namespace toy{
class File;
class ImageBuffer;
}

namespace toy{
namespace webp{

TOY_API_WEBP bool LoadWebp(::toy::File *fileSystemDevice,::toy::ImageBuffer *imageBuffer);

}}
