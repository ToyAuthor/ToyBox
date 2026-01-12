#include "toy/Oops.hpp"
#include "toy/math/FormatConvert.hpp"
#include "toy/math/NumberFormat.hpp"

namespace toy{
namespace math{

static auto RawHexToDec(const std::string& str)->std::string
{
	return str;
}

auto HexToDec(const std::string& str)->std::string
{
	NumberFormat  report(str);

	if ( report.isHexadecimal() )
	{
		toy::Oops(TOY_MARK);
		return "error";
	}

	const char *cstr = str.c_str();
	int offset = 0;

	if ( cstr[offset]=='-' )
	{
		offset += 1;
	}

	offset += 2;

	std::string num = (cstr+offset);

	num = RawHexToDec(num);

	if ( report.isNegative() )
	{
		return std::string("-") + num;
	}

	return num;
}

static auto RawDecToHex(const std::string& str)->std::string
{
	return str;
}

auto DecToHex(const std::string& str)->std::string
{
	NumberFormat  report(str);

	if ( report.isNegative() )
	{
		return std::string("-0x") + RawDecToHex(str);
	}

	return std::string("0x") + RawDecToHex(str);
}

}}
