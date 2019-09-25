#include <cstring>
#include <gmp.h>
#include "toy/Exception.hpp"
#include "toy/math/SafeInt.hpp"
#include "toy/math/NumberFormat.hpp"
#include "toy/bignum/Num.hpp"
#include "toy/bignum/Int.hpp"

namespace toy{
namespace bignum{

struct NumPrivate
{
	NumPrivate()
	{
		mpf_init(number);
	}

	~NumPrivate()
	{
		mpf_clear(number);
	}

	mpf_t number;
};

}}

using namespace toy;
using namespace bignum;

Num::Num():_this(new NumPrivate)
{
	mpf_set_ui(_this->number, 0);
}

Num::~Num()
{
	;
}

Num::Num(const Num& number):_this(new NumPrivate)
{
	mpf_set(_this->number, number._this->number);
}

Num::Num(double number):_this(new NumPrivate)
{
	mpf_set_d(_this->number, number);
}

static void StringToNumClass(NumPrivate *obj,const std::string& str)
{
	toy::math::NumberFormat  report(str);

	if ( report.isGood() )
	{
		if ( report.isDecimal() )
		{
			mpf_set_str(obj->number, str.c_str(), 10);
		}
		else if ( report.isHexadecimal() )
		{
			std::string  temp = str;

			if ( temp[0]=='-' )
			{
				temp[2] = '-';
			}

			mpf_set_str(obj->number, temp.c_str()+2, 16);
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

Num::Num(const std::string& str):_this(new NumPrivate)
{
	StringToNumClass(_this.get(),str);
}

void Num::operator = (std::string number)
{
	StringToNumClass(_this.get(),number);
}

void Num::operator = (double number)
{
	mpf_set_d(_this->number, number);
}

void Num::operator = (const toy::bignum::Int &number)
{
	mpf_set_z(_this->number, *(static_cast<const mpz_t*>(number._getCore())));
}

bool Num::get(double *number) const
{
	*number = mpf_get_d(_this->number);
	return true;
}

static bool GetGmpString( std::string* bufferString, int baseNum, mpf_t &number )
{
	size_t   baseSize = 16;

	std::string  buffer;

	buffer.resize(baseSize);

	mp_exp_t expptr;

	mpf_get_str(const_cast<char*>(buffer.c_str()), &expptr, baseNum, baseSize+1, number);

	if ( buffer[0]=='\0' )
	{
		(*bufferString) = "0";
		return true;
	}

	auto expptrn = ::toy::math::SafeInt<size_t>(expptr,TOY_MARK);

	if ( expptrn>baseSize )
	{
		baseSize = expptrn+3;

		buffer.resize(baseSize);

		mpf_get_str(const_cast<char*>(buffer.c_str()), &expptr, baseNum, baseSize+1, number);
	}

	buffer.resize(std::strlen(buffer.c_str()));

	mp_exp_t expCount = 0;

	bufferString->clear();

	if ( buffer[0]=='-' )
	{
		expCount = -1;

		if ( baseNum==16 )
		{
			bufferString->push_back('-');
			bufferString->push_back('0');
		}
	}
	else
	{
		if ( baseNum==16 )
		{
			bufferString->push_back('0');
			bufferString->push_back('x');
		}
	}

	for ( auto &x : buffer )
	{
		if ( expCount==expptr )
		{
			bufferString->push_back('.');
		}

		expCount++;

		bufferString->push_back(x);
	}

	if ( expCount<expptr )
	{
		expCount = expptr-expCount;

		for (;expCount!=0;expCount--)
		{
			bufferString->push_back('0');
		}
	}

	if ( buffer[0]=='-' && baseNum==16 )
	{
		(*bufferString)[2] = '-';
	}

	return true;
}

bool Num::get(std::string *number) const
{
	return GetGmpString(number,10,_this->number);
}

bool Num::getHex(std::string *number) const
{
	return GetGmpString(number,16,_this->number);
}

auto Num::str() const -> const std::string
{
	std::string str;

	if ( ! this->get(&str) )
	{
		throw toy::Exception(TOY_MARK);
	}

	return str;
}

auto Num::operator + (const Num &number) const -> const Num
{
	Num  result;

	mpf_add(result._this->number, _this->number, number._this->number);

	return result;
}

auto Num::operator - (const Num &number) const -> const Num
{
	Num  result;

	mpf_sub(result._this->number, _this->number, number._this->number);

	return result;
}

auto Num::operator * (const Num &number) const -> const Num
{
	Num  result;

	mpf_mul(result._this->number, _this->number, number._this->number);

	return result;
}

auto Num::operator / (const Num &number) const -> const Num
{
	Num  quotient;

	mpf_div(quotient._this->number, _this->number, number._this->number);

	return quotient;
}

void Num::operator +=(const Num &number)
{
	*this = *this + number;
}

void Num::operator -=(const Num &number)
{
	*this = *this - number;
}

void Num::operator *=(const Num &number)
{
	*this = *this * number;
}

void Num::operator /=(const Num &number)
{
	*this = *this / number;
}

bool Num::negative() const
{
	if ( mpf_cmp_ui(_this->number, 0)==-1 )
	{
		return true;
	}

	return false;
}

void Num::operator = (const Num& number)
{
	mpf_set(_this->number, number._this->number);
}

bool Num::operator > (const Num &number) const
{
	if ( mpf_cmp(_this->number, number._this->number)>0 )
	{
		return true;
	}

	return false;
}

bool Num::operator < (const Num &number) const
{
	if ( mpf_cmp(_this->number, number._this->number)<0 )
	{
		return true;
	}

	return false;
}

bool Num::operator ==(const Num &number) const
{
	if ( mpf_cmp(_this->number, number._this->number)==0 )
	{
		return true;
	}

	return false;
}

bool Num::operator !=(const Num &number) const
{
	if ( mpf_cmp(_this->number, number._this->number)==0 )
	{
		return false;
	}

	return true;
}

bool Num::operator >=(const Num &number) const
{
	if ( mpf_cmp(_this->number, number._this->number)>-1 )
	{
		return true;
	}

	return false;
}

bool Num::operator <=(const Num &number) const
{
	if ( mpf_cmp(_this->number, number._this->number)<1 )
	{
		return true;
	}

	return false;
}
