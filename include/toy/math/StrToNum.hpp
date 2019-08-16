
#pragma once

#include <string>
#include "toy/math/Export.hpp"
#include "toy/math/Num.hpp"

namespace toy{
namespace math{

class TOY_API_MATH _PrimaryNumber
{
	public:

		_PrimaryNumber(const std::string &str);
		~_PrimaryNumber();

		operator float();
		operator double();
		operator   int8_t();
		operator  uint8_t();
		operator  int16_t();
		operator uint16_t();
		operator  int32_t();
		operator uint32_t();
		operator  int64_t();
		operator uint64_t();
		operator ::toy::math::Num();

	private:

		::toy::math::Num  _number;
};

/*
 * Usage:
 *     float  numA = toy::math::StrToNum("3.1415");
 *     int8_t numB = toy::math::StrToNum("23");
 */
TOY_API_MATH extern auto StrToNum(std::string)->_PrimaryNumber;

}}
