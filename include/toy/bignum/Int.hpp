
#pragma once

#include <memory>
#include <string>
#include "toy/bignum/Export.hpp"

namespace toy{
namespace bignum{

struct IntPrivate;

class TOY_API_BIGNUM Int
{
	public:

		~Int();
		Int();
		Int(int32_t            number);
		Int(uint32_t           number);
		Int(const Int&         number);
		Int(const std::string& number);

		bool get(std::string *number) const;
		bool getHex(std::string *number) const;
		auto str() const -> const std::string;

		auto operator + (const Int &number) const -> const Int;
		auto operator - (const Int &number) const -> const Int;
		auto operator * (const Int &number) const -> const Int;
		auto operator / (const Int &number) const -> const Int;
		auto operator % (const Int &number) const -> const Int;
		void operator +=(const Int &number);
		void operator -=(const Int &number);
		void operator *=(const Int &number);
		void operator /=(const Int &number);
		void operator %=(const Int &number);

		void operator = (const Int &number);
		void operator = (int32_t     number);
		void operator = (uint32_t    number);
		void operator = (std::string number);

		bool operator > (const Int &number) const;
		bool operator < (const Int &number) const;
		bool operator ==(const Int &number) const;
		bool operator !=(const Int &number) const;
		bool operator >=(const Int &number) const;
		bool operator <=(const Int &number) const;

		auto divide(const Int &number) -> const Int;
		bool negative() const;

	private:

		std::unique_ptr<IntPrivate> _this;
};

}}
