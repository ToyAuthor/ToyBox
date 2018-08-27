#include <gmp.h>
#include "toy/Exception.hpp"
#include "toy/math/NumberFormat.hpp"
#include "toy/bignum/Int.hpp"

namespace toy{
namespace bignum{

struct IntPrivate
{
	IntPrivate()
	{
		mpz_init(number);
	}

	~IntPrivate()
	{
		mpz_clear(number);
	}

	mpz_t number;
};

}}

using namespace toy;
using namespace bignum;

Int::Int():_this(new IntPrivate)
{
	mpz_set_ui(_this->number, 0);
}

Int::~Int()
{
	delete _this;
}

Int::Int(const Int& number):_this(new IntPrivate)
{
	mpz_set(_this->number, number._this->number);
}

Int::Int(int32_t number):_this(new IntPrivate)
{
	double  temp = number;
	mpz_set_d(_this->number, temp);
}

Int::Int(uint32_t number):_this(new IntPrivate)
{
	double  temp = number;
	mpz_set_d(_this->number, temp);
}

static void StringToIntClass(IntPrivate *obj,const std::string& str)
{
	toy::math::NumberFormat  report(str);

	if ( report.isGood() && report.isInteger() )
	{
		if ( report.isDecimal() )
		{
			mpz_set_str(obj->number, str.c_str(), 10);
		}
		else if ( report.isHexadecimal() )
		{
			mpz_set_str(obj->number, str.c_str(), 0);
		}
		else
		{
			throw toy::Exception(TOY_MARK);
		}
	}
	else
	{
		throw toy::Exception(TOY_MARK);
	}
}

Int::Int(const std::string& str):_this(new IntPrivate)
{
	StringToIntClass(_this,str);
}

void Int::operator = (std::string number)
{
	StringToIntClass(_this,number);
}

void Int::operator = (int32_t number)
{
	double  temp = number;
	mpz_set_d(_this->number, temp);
}

void Int::operator = (uint32_t number)
{
	double  temp = number;
	mpz_set_d(_this->number, temp);
}

bool Int::get(std::string *number) const
{
	auto  size = mpz_sizeinbase(_this->number, 10) + 2;

	char  *buffer = new char[size];

	if ( buffer==nullptr )
	{
		return false;
	}

	mpz_get_str(buffer, 10, _this->number);

	*number = buffer;

	delete buffer;

	return true;
}

bool Int::getHex(std::string *number) const
{
	auto  size = mpz_sizeinbase(_this->number, 10) + 4;

	char  *buffer = new char[size];

	if ( buffer==nullptr )
	{
		return false;
	}

	buffer[0] = '0';
	buffer[1] = 'x';
	mpz_get_str(buffer+2, 16, _this->number);

	if ( buffer[2]=='-' )
	{
		buffer[0] = '-';
		buffer[1] = '0';
		buffer[2] = 'x';
	}

	*number = buffer;

	delete buffer;

	return true;
}

auto Int::str() const -> const std::string
{
	std::string str;

	if ( ! this->get(&str) )
	{
		throw toy::Exception(TOY_MARK);
	}

	return str;
}

auto Int::operator + (const Int &number) const -> const Int
{
	Int  result;

	mpz_add(result._this->number, _this->number, number._this->number);

	return result;
}

auto Int::operator - (const Int &number) const -> const Int
{
	Int  result;

	mpz_sub(result._this->number, _this->number, number._this->number);

	return result;
}

auto Int::operator * (const Int &number) const -> const Int
{
	Int  result;

	mpz_mul(result._this->number, _this->number, number._this->number);

	return result;
}

auto Int::operator / (const Int &number) const -> const Int
{
	Int  quotient;

	mpz_fdiv_q(quotient._this->number, _this->number, number._this->number);

	return quotient;
}

auto Int::operator % (const Int &number) const -> const Int
{
	Int  residue;

	mpz_fdiv_r(residue._this->number, _this->number, number._this->number);

	return residue;
}

void Int::operator +=(const Int &number)
{
	*this = *this + number;
}

void Int::operator -=(const Int &number)
{
	*this = *this - number;
}

void Int::operator *=(const Int &number)
{
	*this = *this * number;
}

void Int::operator /=(const Int &number)
{
	*this = *this / number;
}

void Int::operator %=(const Int &number)
{
	*this = *this % number;
}

auto Int::divide(const Int &number) -> const Int
{
	Int  residue;

	mpz_t   quotient;
	mpz_init(quotient);

	mpz_fdiv_qr(quotient, residue._this->number, _this->number, number._this->number);

	mpz_swap(quotient, _this->number);
	mpz_clear(quotient);

	return residue;
}

bool Int::negative() const
{
	if ( mpz_cmp_ui(_this->number, 0)==-1 )
	{
		return true;
	}

	return false;
}

void Int::operator = (const Int& number)
{
	mpz_set(_this->number, number._this->number);
}

bool Int::operator > (const Int &number) const
{
	if ( mpz_cmp(_this->number, number._this->number)>0 )
	{
		return true;
	}

	return false;
}

bool Int::operator < (const Int &number) const
{
	if ( mpz_cmp(_this->number, number._this->number)<0 )
	{
		return true;
	}

	return false;
}

bool Int::operator ==(const Int &number) const
{
	if ( mpz_cmp(_this->number, number._this->number)==0 )
	{
		return true;
	}

	return false;
}

bool Int::operator !=(const Int &number) const
{
	if ( mpz_cmp(_this->number, number._this->number)==0 )
	{
		return false;
	}

	return true;
}

bool Int::operator >=(const Int &number) const
{
	if ( mpz_cmp(_this->number, number._this->number)>-1 )
	{
		return true;
	}

	return false;
}

bool Int::operator <=(const Int &number) const
{
	if ( mpz_cmp(_this->number, number._this->number)<1 )
	{
		return true;
	}

	return false;
}
