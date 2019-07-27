
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

// ASCII -> text
//  27 -> "[ESC]"
//  97 -> "a"
// 101 -> "e"
//  48 -> "0"
TOY_API_GADGET extern auto AnsiNumToStr(int key)->std::string;

}}
