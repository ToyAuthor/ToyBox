
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

// '1' -> 1
// '9' -> 9
// 'a' -> 10
// 'A' -> 10
// 'f' -> 15
// 'g' -> [error]
TOY_API_GADGET extern int HexCharToInt(const char);

}}
