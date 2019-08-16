
#pragma once

#include <cstdint>
#include <string>
#include "toy/math/Export.hpp"
#include "toy/math/Int.hpp"

namespace toy{
namespace math{

struct NumPrivate;

class TOY_API_MATH Num
{
	public:

		~Num();
		Num();
		Num(std::string number);

		bool get( int8_t     *number) const;
		bool get(uint8_t     *number) const;
		bool get( int16_t    *number) const;
		bool get(uint16_t    *number) const;
		bool get( int32_t    *number) const;
		bool get(uint32_t    *number) const;
		bool get( int64_t    *number) const;
		bool get(uint64_t    *number) const;
		bool get(float       *number) const;
		bool get(double      *number) const;
		bool getHex(std::string *number) const;

		auto operator + (const Num &number) const -> const Num;

		void setForTest(const uint8_t* ptr, uint32_t size, bool isNegative, uint32_t offset);

	private:

		NumPrivate* _this = nullptr;
};

}}
