
#pragma once

#include <cstdint>
#include <string>
#include "toy/math/Export.hpp"

namespace toy{
namespace math{

struct IntPrivate;

class TOY_API_MATH Int
{
	public:

		~Int();
		Int();
		Int(const Int&  number);
		Int(int8_t      number);
		Int(uint8_t     number);
		Int(int16_t     number);
		Int(uint16_t    number);
		Int(int32_t     number);
		Int(uint32_t    number);
		Int(int64_t     number);
		Int(uint64_t    number);
		Int(std::string number);

		auto str() const -> const std::string;

		bool get( int8_t     *number) const;
		bool get(uint8_t     *number) const;
		bool get( int16_t    *number) const;
		bool get(uint16_t    *number) const;
		bool get( int32_t    *number) const;
		bool get(uint32_t    *number) const;
		bool get( int64_t    *number) const;
		bool get(uint64_t    *number) const;
		bool get(std::string *number) const;
		bool getHex(std::string *number) const;

		void setRawData(const uint8_t* ptr, uint32_t size, bool isNegative);

		void operator = (const Int&  number);
		void operator = (int8_t      number);
		void operator = (uint8_t     number);
		void operator = ( int16_t    number);
		void operator = (uint16_t    number);
		void operator = ( int32_t    number);
		void operator = (uint32_t    number);
		void operator = ( int64_t    number);
		void operator = (uint64_t    number);
		void operator = (std::string number);

		auto operator + (const Int &number) const -> const Int;
		auto operator - (const Int &number) const -> const Int;
		auto operator * (const Int &number) const -> const Int;
		auto operator / (const Int &number) const -> const Int;
		auto operator % (const Int &number) const -> const Int;
		auto operator ^ (const Int &number) const -> const Int;
		void operator +=(const Int &number);
		void operator -=(const Int &number);
		void operator *=(const Int &number);
		void operator /=(const Int &number);
		void operator %=(const Int &number);
		void operator ^=(const Int &number);

		bool operator > (const Int &number) const;
		bool operator < (const Int &number) const;
		bool operator ==(const Int &number) const;
		bool operator !=(const Int &number) const;
		bool operator >=(const Int &number) const;
		bool operator <=(const Int &number) const;
		bool operator > (int32_t    number) const;
		bool operator < (int32_t    number) const;
		bool operator ==(int32_t    number) const;
		bool operator !=(int32_t    number) const;
		bool operator >=(int32_t    number) const;
		bool operator <=(int32_t    number) const;

		auto divide(const Int &number) -> const Int;
		bool isAbsoluteValueBiggerThan (const Int &number);
		bool isAbsoluteValueSmallerThan(const Int &number);

		auto size() const -> uint32_t;
		auto data() const -> const uint8_t*;
		bool negative() const;

	private:

		IntPrivate* _this = nullptr;
};

}}
