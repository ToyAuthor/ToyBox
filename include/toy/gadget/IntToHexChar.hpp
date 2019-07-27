
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

//  1 -> '1'
//  2 -> '2'
// 11 -> 'b'
// 15 -> 'f'
// 16 -> [error]
TOY_API_GADGET extern char IntToHexChar(int);

//  1 -> '1'
//  2 -> '2'
// 11 -> 'B'
// 15 -> 'F'
// 16 -> [error]
TOY_API_GADGET extern char IntToHexChar_Capital(int);

}}
