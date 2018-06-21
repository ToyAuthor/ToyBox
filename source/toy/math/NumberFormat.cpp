
#include "toy/math/NumberFormat.hpp"

namespace toy{
namespace math{

struct NumberFormatPrivate
{
	uint8_t   isGood           : 1;
	uint8_t   isInteger        : 1;
	uint8_t   isNegative       : 1;
	uint8_t   isDecimal        : 1;
	uint8_t   isHexadecimal    : 1;
	uint8_t   : 0;
};

}}

using namespace toy;
using namespace math;

auto NumberFormat::operator = ( const NumberFormat & m ) -> const NumberFormat&
{
	*_this = *(m._this);
	return *this;
}

NumberFormat::NumberFormat(const NumberFormat & m):_this(new NumberFormatPrivate)
{
	*_this = *(m._this);
}

static bool IsNumberChar(char c)
{
	if ( c<'0' || c>'9' )
	{
		return false;
	}

	return true;
}

static bool IsHexNumberChar(char c)
{
	if ( ( c<'0' || c>'9' ) && ( c<'a' || c>'f' ) )
	{
		return false;
	}

	return true;
}

NumberFormat::NumberFormat(const std::string &num):_this(new NumberFormatPrivate)
{
	*((uint8_t*)_this) = uint8_t(0);

	int size = num.size();

	if ( size==0 )
	{
		return;
	}

	int index = 0;

	if ( num[index]=='-' )
	{
		index++;
		_this->isNegative = 1;
	}

	if ( size<index+2 ) return;

	bool maybeIsHexadecimal = false;
	bool dotFound = false;

	bool (*func)(char) = IsNumberChar;

	if ( num[index]=='0' )
	{
		if ( size<index+2 ) return;

		if ( num[index+1]=='x' )
		{
			if ( size<index+3 ) return;

			func = IsHexNumberChar;
			index += 2;
			maybeIsHexadecimal = true;

			if ( num[index]=='0' )
			{
				if ( size<index+2 )
				{
					return;   // 0x0
				}
				else
				{
					if ( num[index+1]=='.' )
					{
						if ( size<index+3 ) return; // 0x0.

						dotFound = true;
						index += 2;
					}
					else
					{
						return;   // 0x0123
					}
				}
			}
			else if ( num[index]=='.' )
			{
				return;
			}
		}
		else if ( num[index+1]=='.' )
		{
			if ( size<index+3 ) return;  // 0x0.

			dotFound = true;
			index += 2;
		}
		else
		{
			return;
		}
	}
	else if ( num[index]=='.' )
	{
		return;
	}

	for (; size>index ;index++)
	{
		if ( num[index]=='.' )
		{
			if ( dotFound )
			{
				return;
			}
			else
			{
				dotFound = true;
			}
		}
		else if ( ! func(num[index]) ) return;
	}

	if ( num[size-1]=='.' )
	{
		return;   // xxx.
	}

	_this->isGood = 1;

	if ( maybeIsHexadecimal )
	{
		_this->isHexadecimal = 1;
	}
	else
	{
		_this->isDecimal = 1;
	}

	if ( dotFound==false )
	{
		_this->isInteger = 1;
	}
}

NumberFormat::~NumberFormat()
{
	delete _this;
}

bool NumberFormat::isGood()
{
	return _this->isGood;
}

bool NumberFormat::isInteger()
{
	return _this->isInteger;
}

bool NumberFormat::isNegative()
{
	return _this->isNegative;
}

bool NumberFormat::isDecimal()
{
	return _this->isDecimal;
}

bool NumberFormat::isHexadecimal()
{
	return _this->isHexadecimal;
}
