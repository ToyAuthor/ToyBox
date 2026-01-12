#include "toy/gadget/VariableLengthInteger.hpp"

namespace toy{
namespace gadget{

bool WriteUnsignedVariableLengthInteger( uint64_t                     number,
                                         std::function<bool(uint8_t)> func )
{
	uint64_t temp;
	uint64_t quotient = number;
	uint64_t residue;

	for ( int count = 1 ; count<9 ; count++ )
	{
		temp = quotient;
		quotient = quotient / 127;
		residue = temp - quotient*127;

		if ( quotient>0 )
		{
			if ( func(residue+128) )
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if ( func(residue) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool ReadUnsignedVariableLengthInteger( uint64_t*                     number,
                                        std::function<bool(uint8_t*)> func )
{
	uint8_t num = 0;

	*number = 0;

	uint64_t  innum = 1;

	for ( int count = 1 ; count<9 ; count++ )
	{
		if ( false==func(&num) )
		{
			return false;
		}

		if ( num>127 )
		{
			num = num-128;
			*number += uint64_t(num)*innum;
		}
		else
		{
			*number += uint64_t(num)*innum;
			return true;
		}

		innum *= 127;
	}

	return false;
}

bool WriteVariableLengthInteger( int64_t                      number,
                                 std::function<bool(uint8_t)> func )
{
	bool isNegative = false;

	if ( number<0 )
	{
		isNegative = true;
		number *= -1;
	}

	int64_t quotient = number;
	int64_t temp = quotient;

	quotient = quotient / 63;

	int64_t residue = temp - quotient*63;

	if ( isNegative )
	{
		residue += 64;
	}

	if ( quotient>0 )
	{
		if ( false==func(residue+128) )
		{
			return false;
		}
	}
	else
	{
		if ( func(residue) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	for ( int count = 1 ; count<8 ; count++ )
	{
		temp = quotient;
		quotient = quotient / 127;
		residue = temp - quotient*127;

		if ( quotient>0 )
		{
			if ( func(residue+128) )
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if ( func(residue) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool ReadVariableLengthInteger( int64_t*                      number,
                                std::function<bool(uint8_t*)> func )
{
	bool isNegative = false;

	uint8_t num = 0;

	*number = 0;

	int64_t  innum = 1;

	//--------------------------------------------------------
	if ( false==func(&num) )
	{
		return false;
	}

	if ( num>127 )
	{
		num = num-128;

		if ( num>63 )
		{
			num = num-64;
			isNegative = true;
		}

		*number += int64_t(num)*innum;
	}
	else
	{
		if ( num>63 )
		{
			num = num-64;
			isNegative = true;
		}

		*number += int64_t(num)*innum;

		if ( isNegative )
		{
			(*number) *= -1;
		}

		return true;
	}

	innum *= 63;
	//--------------------------------------------------------

	for ( int count = 1 ; count<8 ; count++ )
	{
		if ( false==func(&num) )
		{
			return false;
		}

		if ( num>127 )
		{
			num = num-128;
			*number += int64_t(num)*innum;
		}
		else
		{
			*number += int64_t(num)*innum;

			if ( isNegative )
			{
				(*number) *= -1;
			}

			return true;
		}

		innum *= 127;
	}

	return false;
}

}}
