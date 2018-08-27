
#pragma once

#include <cstdint>
#include <string>
#include "toy/math/Export.hpp"

namespace toy{
namespace math{

struct Int2Private;

class TOY_API_MATH Int2
{
	public:

		~Int2();
		Int2();
		Int2(const Int2& number);
		Int2(int8_t      number);
		Int2(uint8_t     number);
		Int2(int16_t     number);
		Int2(uint16_t    number);
		Int2(int32_t     number);
		Int2(uint32_t    number);
		Int2(std::string number);

		auto str() const -> const std::string;

		bool get( int8_t  *number) const;
		bool get(uint8_t  *number) const;
		bool get(std::string *number) const;

		void operator = (const Int2&);
		void operator = (int32_t num);
		void operator = (std::string number);

		auto operator + (const Int2&) const -> const Int2;
		auto operator - (const Int2&) const -> const Int2;
		auto operator * (const Int2&) const -> const Int2;
		auto operator / (const Int2&) const -> const Int2;
		auto operator % (const Int2&) const -> const Int2;
		void operator +=(const Int2&);
		void operator -=(const Int2&);
		void operator *=(const Int2&);
		void operator /=(const Int2&);
		void operator %=(const Int2&);

		bool operator > (const Int2&) const;
		bool operator < (const Int2&) const;
		bool operator ==(const Int2&) const;
		bool operator !=(const Int2&) const;
		bool operator >=(const Int2&) const;
		bool operator <=(const Int2&) const;
		bool operator > (int32_t num) const;
		bool operator < (int32_t num) const;
		bool operator ==(int32_t num) const;
		bool operator >=(int32_t num) const;
		bool operator <=(int32_t num) const;

		auto divide(const Int2&) -> const Int2;
		bool isAbsoluteValueBiggerThan (const Int2 &number);
		bool isAbsoluteValueSmallerThan(const Int2 &number);

	private:

		Int2Private* _this = nullptr;
};

}}
