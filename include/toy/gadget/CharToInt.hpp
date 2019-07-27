
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

// '1' -> 1
// '9' -> 9
// 'a' -> [error]
// 'A' -> [error]
// 'f' -> [error]
// 'g' -> [error]
TOY_API_GADGET extern int CharToInt(const char);

}}
