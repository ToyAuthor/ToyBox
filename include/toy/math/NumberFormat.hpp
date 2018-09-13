
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
		bool isDecimal();         // Something like 123,-123,123.4
		bool isHexadecimal();     // Something like 0x123a1,-0xff.f

		auto operator = ( const NumberFormat & ) -> const NumberFormat&;

	private:

		struct NumberFormatPrivate *_this = nullptr;
};

}}
