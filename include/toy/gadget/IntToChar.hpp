
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

//  1 -> '1'
//  2 -> '2'
//  9 -> '9'
// 10 -> [error]
// -1 -> [error]
TOY_API_GADGET extern char IntToChar(int);

}}
