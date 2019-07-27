
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

// text -> ASCII
// "[ESC]" -> 27
// "0" -> 48
// "a" -> 97
TOY_API_GADGET extern char StrToAscii(const std::string &);
TOY_API_GADGET extern char StrToAscii(const char*);

}}
