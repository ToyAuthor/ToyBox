#include "toy/Oops.hpp"
#include "toy/math/StrToNum.hpp"

namespace toy{
namespace math{

auto StrToNum(std::string str)->_PrimaryNumber
{
	return _PrimaryNumber(str);
}

}}

using namespace toy;
using namespace math;

_PrimaryNumber::_PrimaryNumber(const std::string &str):_number(str)
{
	;
}

_PrimaryNumber::~_PrimaryNumber()
{
	;
}

_PrimaryNumber::operator float()
{
	float   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return float(0);
	}

	return number;
}

_PrimaryNumber::operator double()
{
	double   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return double(0);
	}

	return number;
}

_PrimaryNumber::operator int8_t()
{
	int8_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return int8_t(0);
	}

	return number;
}

_PrimaryNumber::operator uint8_t()
{
	uint8_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return uint8_t(0);
	}

	return number;
}

_PrimaryNumber::operator int16_t()
{
	int16_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return int16_t(0);
	}

	return number;
}

_PrimaryNumber::operator uint16_t()
{
	uint16_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return uint16_t(0);
	}

	return number;
}

_PrimaryNumber::operator int32_t()
{
	int32_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return int32_t(0);
	}

	return number;
}

_PrimaryNumber::operator uint32_t()
{
	uint32_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return uint32_t(0);
	}

	return number;
}

_PrimaryNumber::operator int64_t()
{
	int64_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return int64_t(0);
	}

	return number;
}

_PrimaryNumber::operator uint64_t()
{
	uint64_t   number = 0;

	if ( ! _number.get(&number) )
	{
		toy::Oops(TOY_MARK);
		return uint64_t(0);
	}

	return number;
}

_PrimaryNumber::operator ::toy::math::Num()
{
	return _number;
}
