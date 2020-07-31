
#pragma once

#include "toy/Option.hpp"
#include "toy/Color.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/photo/Export.hpp"

namespace toy{
namespace photo{

TOY_API_PHOTO extern void Flip(toy::ImageBuffer *image,enum toy::Option);
TOY_API_PHOTO extern void Flip(const toy::ImageBuffer &input,toy::ImageBuffer *output,enum toy::Option);
TOY_API_PHOTO extern void Resize(toy::ImageBuffer *image,int32_t topward,int32_t downward,int32_t leftward,int32_t rightward);
TOY_API_PHOTO extern void ToRGBA001(toy::ImageBuffer *image);
TOY_API_PHOTO extern void ToRGBA001(toy::ImageBuffer *image,const toy::Color &color);
TOY_API_PHOTO extern void ToRGBA001(const toy::ImageBuffer &input,toy::ImageBuffer *output);
TOY_API_PHOTO extern void ToRGBA001(const toy::ImageBuffer &input,toy::ImageBuffer *output,const toy::Color &color);
TOY_API_PHOTO extern void BaseOnTwo(toy::ImageBuffer *image);

}}
