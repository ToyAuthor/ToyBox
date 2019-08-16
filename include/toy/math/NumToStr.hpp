
#pragma once

#include <string>
#include "toy/math/Int.hpp"

namespace toy{
namespace math{

static inline auto NumToStr(::toy::math::Int num)->std::string
{
	return num.str();
}

}}
