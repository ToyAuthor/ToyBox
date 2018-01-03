
#pragma once

#include <string>
#include "toy/math/Export.hpp"

namespace toy{
namespace math{

struct NumberFormatPrivate;

class TOY_API_MATH NumberFormat
{
	public:

		NumberFormat(const std::string &);
		NumberFormat(const NumberFormat &);
		~NumberFormat();

		bool isGood();
		bool isInteger();
		bool isNegative();
		bool isDecimal();
		bool isHexadecimal();

		auto operator = ( const NumberFormat & ) -> const NumberFormat&;

	private:

		struct NumberFormatPrivate *_this = nullptr;
};

TOY_API_MATH extern auto GetNumberFormat(const std::string &)->NumberFormat;

TOY_API_MATH extern auto HexToDec(const std::string &)->std::string;

TOY_API_MATH extern auto DecToHex(const std::string &)->std::string;

}}
