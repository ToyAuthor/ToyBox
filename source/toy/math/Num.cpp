#include <vector>
#include <limits>
#include "toy/Oops.hpp"
#include "toy/Exception.hpp"
#include "toy/gadget/HexCharToInt.hpp"
#include "toy/math/Num.hpp"
#include "toy/math/Int.hpp"
#include "toy/math/NumberFormat.hpp"

namespace toy{
namespace math{

struct NumPrivate
{
	::toy::math::Int    number;
	uint32_t            offset = 0;
};

}}

using namespace toy;
using namespace math;

Num::~Num()
{
	delete _this;
}

Num::Num():_this(new struct NumPrivate)
{
	;
}

void Num::setForTest(const uint8_t* ptr, uint32_t size, bool isNegative, uint32_t offset)
{
	_this->number.setRawData(ptr,size,isNegative);
	_this->offset = offset;
}

static uint32_t FindPointPosition(const std::string &str)
{
	uint32_t   count = 0;

	const char *start = str.c_str();
	const char *ptr = &(str[str.size()-1]);

	for ( ; ptr!=start; --ptr )
	{
		count += 1;

		if ( *ptr=='.' )
		{
			return count-1;
		}
	}

	throw toy::Exception(TOY_MARK);
	return 0;
}

static bool IsOddNumber(const char *start, const char ending)
{
	bool  result = false;

	for ( ; *start != ending ; start+=1 )
	{
		result = ! result;
	}

	return result;
}

static void HexStringToInt(const std::string &str,std::vector<uint8_t> *raw, uint32_t offset)
{
	const char* head  = str.c_str();
	const char* ptr   = &(str[str.size()-1]);
	const char* point = ptr-offset;

	if ( *head=='-' )
	{
		head += 1;
	}

	head += 2;

	uint8_t   temp = 0;

	if ( IsOddNumber(point+1,'\0') )
	{
		temp = uint8_t(::toy::gadget::HexCharToInt(*ptr));
		temp <<= 4;
		raw->push_back(temp);
	}
	else
	{
		ptr += 1;
	}

	if ( (ptr-1)!=point )
	{
		do
		{
			ptr -= 2;

			temp = uint8_t(::toy::gadget::HexCharToInt(*ptr));
			temp <<= 4;
			temp += uint8_t(::toy::gadget::HexCharToInt(*(ptr+1)));
			raw->push_back(temp);
		}
		while ( (ptr-1)!=point );
	}

	ptr -= 2;

	int  isOdd = IsOddNumber(head,'.')?1:0;

	for ( ; *(ptr-isOdd)!='x' ; ptr-=2 )
	{
		toy::Logger<<"ptr1:"<<(uint8_t)(*(ptr-1))<<toy::NewLine;
		toy::Logger<<"ptr2:"<<(uint8_t)(*(ptr))<<toy::NewLine;
		temp = uint8_t(::toy::gadget::HexCharToInt(*(ptr-1)));
		temp <<= 4;
		temp += uint8_t(::toy::gadget::HexCharToInt(*(ptr)));
		raw->push_back(temp);

		toy::Logger<<"temp:"<<temp<<toy::NewLine;
	}

	if ( isOdd==1 )
	{
		raw->push_back(uint8_t(::toy::gadget::HexCharToInt(*ptr)));
	}
}

Num::Num(std::string str):_this(new struct NumPrivate)
{
	NumberFormat  report(str);

	if ( report.isGood()==false )
	{
		throw toy::Exception(TOY_MARK);
		return;
	}

	if ( report.isInteger()==true )
	{
		_this->number = str;
		_this->offset = 0;
		return;
	}

	uint32_t  offset = FindPointPosition(str);
	_this->offset = (offset+1)>>1;

	std::vector<uint8_t>   raw;

	bool        isNegative = false;

	if ( *(str.c_str())=='-' )
	{
		isNegative = true;
	}

	if ( report.isHexadecimal()==true )
	{
		HexStringToInt(str,&raw,offset);
	}
	else
	{
		throw toy::Exception(TOY_MARK);
	}

	_this->number.setRawData(raw.data(),raw.size(),isNegative);
}

bool Num::get(int8_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(uint8_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	if ( _this->number.negative() )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(int16_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(uint16_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	if ( _this->number.negative() )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(int32_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(uint32_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	if ( _this->number.negative() )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(int64_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(uint64_t *number) const
{
	if ( _this->offset!=0 )
	{
		return false;
	}

	if ( _this->number.negative() )
	{
		return false;
	}

	return _this->number.get(number);
}

bool Num::get(float *number) const
{
	if ( _this->number.size()<5 )
	{
		int32_t   num = 0;

		if ( _this->number.get(&num)==false )
		{
			uint32_t   num2 = 0;

			if ( _this->number.get(&num2) )
			{
				toy::Oops(TOY_MARK);
				return false;
			}

			*number = num2;
		}

		*number = num;
	}
	else
	{
		uint32_t  num = 0;

		const uint8_t *ptr = _this->number.data();
		ptr += (_this->number.size()-1);
		num += *ptr;   num <<= 8;   ptr -= 1;
		num += *ptr;   num <<= 8;   ptr -= 1;
		num += *ptr;   num <<= 8;   ptr -= 1;
		num += *ptr;

		*number = num;

		auto offset = _this->number.size()-4;

		for ( auto i=offset;i>0;--i)
		{
			(*number) *= float(256);
		}
	}

	if ( _this->offset>50 )
	{
		*number = float(0);
		return true;
	}

	for ( auto i=_this->offset;i>0;--i)
	{
		(*number) /= float(256);
	}

	return true;
}

bool Num::get(double *number) const
{
	float  temp = 0;
	this->get(&temp);

	*number = temp;

	return true;
}

// Return value:
//     0:failed:
//     1:".":
//     2:"0.":
//     3:"0.0":
//     4:"0.00":
//     5:"0.000":
//     6:"0.0000":
static std::string::size_type GetNeedSize( std::string::size_type  offset,
                                           std::string::size_type  strSize )
{
	if ( offset>=strSize )
	{
		return (offset-strSize)+2;
	}
	else
	{
		return 1;
	}

	return 0;
}

static void MoveString( std::string*           str,
                        std::string::size_type inognor,
                        std::string::size_type step )
{
	auto size = str->size();

	auto index = size-step-1;

	for( ; index!=inognor ; --index)
	{
		(*str)[index+step] = (*str)[index];
	}

	(*str)[index+step] = (*str)[index];
}

static auto ToStringTypeAndCheck(uint32_t num, bool isZeroEnd)->std::string::size_type
{
	auto   maxSize = std::numeric_limits<std::string::size_type>::max();

	if ( sizeof(uint32_t) >= sizeof(std::string::size_type) )
	{
		if ( num > static_cast<uint32_t>(maxSize>>1) )
		{
			toy::Oops(TOY_MARK);
			return 0;
		}
	}

	auto result = static_cast<std::string::size_type>(num);

	if ( isZeroEnd )
	{
		result -= 1;
		result <<= 1;
		result += 1;
	}
	else
	{
		result <<= 1;
	}

	return result;
}

bool Num::getHex(std::string *number) const
{
	if ( ! _this->number.getHex(number) )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( _this->offset==0 ) return true;

	bool       isZeroEnd  = number->back()=='0'?true:false;
	const auto offset     = ToStringTypeAndCheck( _this->offset, isZeroEnd );

	if ( offset==0 )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	bool isNegative = _this->number.negative();

	if ( isZeroEnd )
	{
		number->pop_back();
	}

	auto extSize = GetNeedSize( offset, number->size()-2-(isNegative?1:0));

	if ( extSize==0 )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( ( std::numeric_limits<std::string::size_type>::max() - number->size() )<extSize )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	auto  inognor = number->size() - offset;

	number->resize(number->size() + extSize );

	MoveString(number,inognor,extSize);

	if ( extSize>2 )
	{
		auto i = inognor + extSize - 1;
		inognor += 1;

		for (;i>inognor;i--)
		{
			(*number)[i-2] = '0';
		}

		(*number)[inognor-2] = '.';
		(*number)[inognor-3] = '0';
	}
	else if ( extSize==1 )
	{
		(*number)[inognor] = '.';
	}
	else if ( extSize==2 )
	{
		(*number)[inognor-1] = '.';
		(*number)[inognor-2] = '0';
	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	return true;
}

static inline uint32_t CountZero(const ::toy::math::Int &num)
{
	uint32_t        result = 0;
	auto            size = num.size();
	const uint8_t*  data = num.data();

	for ( uint32_t i=0;i<size;++i )
	{
		if ( data[i]!=0 )
		{
			break;
		}

		++result;
	}

	return result;
}

static inline void RemoveUnusedZero(struct NumPrivate *obj)
{
	if ( obj->offset==0 ) return;

	auto   zero = CountZero(obj->number);

	if (zero==0) return;
	if ( obj->offset<zero ) zero = obj->offset;

	obj->number >>= zero*8;
	obj->offset -= zero;
}

auto Num::operator + (const Num &number) const -> const Num
{
	Num    result;

	if ( _this->offset == number._this->offset )
	{
		result._this->number = _this->number + number._this->number;
		RemoveUnusedZero(result._this);
		return result;
	}

	struct NumPrivate*   obj01;
	struct NumPrivate*   obj02;

	if ( _this->offset > number._this->offset)
	{
		obj01 = _this;
		obj02 = number._this;
	}
	else
	{
		obj01 = number._this;
		obj02 = _this;
	}

	*(result._this) = *obj02;

	obj02 = result._this;

	auto   diff = obj01->offset - obj02->offset;

	obj02->number <<= diff*8;
	obj02->offset += diff;

	obj02->number += obj01->number;

	RemoveUnusedZero(obj02);

	return result;
}
