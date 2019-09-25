
#pragma once

#include <memory>
#include <string>
#include "toy/bignum/Export.hpp"

namespace toy{
namespace bignum{

struct NumPrivate;
class Int;

class TOY_API_BIGNUM Num
{
	public:

		~Num();
		Num();
		Num(double             number);
		Num(const Num&         number);
		Num(const std::string& number);

		bool get(    double      *number) const;
		bool get(    std::string *number) const;
		bool getHex( std::string *number) const;
		auto str() const -> const std::string;

		auto operator + (const Num &number) const -> const Num;
		auto operator - (const Num &number) const -> const Num;
		auto operator * (const Num &number) const -> const Num;
		auto operator / (const Num &number) const -> const Num;
		void operator +=(const Num &number);
		void operator -=(const Num &number);
		void operator *=(const Num &number);
		void operator /=(const Num &number);

		void operator = (const Num &number);
		void operator = (double      number);
		void operator = (std::string number);
		void operator = (const toy::bignum::Int &number);

		bool operator > (const Num &number) const;
		bool operator < (const Num &number) const;
		bool operator ==(const Num &number) const;
		bool operator !=(const Num &number) const;
		bool operator >=(const Num &number) const;
		bool operator <=(const Num &number) const;

		bool negative() const;

	private:

		std::unique_ptr<NumPrivate>  _this;
};

}}
