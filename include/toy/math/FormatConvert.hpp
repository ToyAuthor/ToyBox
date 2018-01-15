
#pragma once

#include <string>
#include "toy/math/Export.hpp"

namespace toy{
namespace math{

TOY_API_MATH extern auto HexToDec(const std::string &)->std::string;

TOY_API_MATH extern auto DecToHex(const std::string &)->std::string;

}}
