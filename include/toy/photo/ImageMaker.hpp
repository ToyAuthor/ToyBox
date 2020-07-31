
#pragma once

#include "toy/photo/Export.hpp"
#include "toy/Color.hpp"
#include "toy/ImageBuffer.hpp"

namespace toy{
namespace photo{

TOY_API_PHOTO extern void MakeCircle( toy::ImageBuffer  *image,
                                      uint32_t          width,
                                      uint32_t          border,
                                      const toy::Color& color );

TOY_API_PHOTO extern void MakeRectangle( toy::ImageBuffer  *image,
                                         uint32_t          width,
                                         uint32_t          height,
                                         uint32_t          border,
                                         const toy::Color& color );

}}
