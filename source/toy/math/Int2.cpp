#include <vector>
#include <memory>
#include <limits>
#include "toy/Mark.hpp"
#include "toy/Exception.hpp"
#include "toy/Log.hpp"
#include "toy/math/Int2.hpp"
#include "toy/math/NumberFormat.hpp"
#include "toy/math/IntCommon.hpp"

namespace toy{
namespace math{

struct Int2Private
{
	std::vector<uint8_t>  data;
	bool                  negative = false;
};

}}

using namespace toy;
using namespace math;

Int2::~Int2()
{
	delete _this;
}

Int2::Int2():_this(new struct Int2Private)
{
	_this->data.push_back(0);
}

Int2::Int2(const Int2 &number):_this(new struct Int2Private)
{
	*_this = *(number._this);
}

Int2::Int2(int8_t number):_this(new struct Int2Private)
{
	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	_this->data.push_back(number);
}

Int2::Int2(uint8_t number):_this(new struct Int2Private)
{
	_this->data.push_back(number);
}

Int2::Int2(int16_t number):_this(new struct Int2Private)
{
	if ( number==0 )
	{
		_this->data.push_back(0);
		return;
	}

	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	int16_t  temp = number%100;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - temp)/100);
}

Int2::Int2(uint16_t number):_this(new struct Int2Private)
{
	if ( number==0 )
	{
		_this->data.push_back(0);
		return;
	}

	uint16_t  temp = number%100;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - temp)/100);
}

Int2::Int2(uint32_t num):_this(new struct Int2Private)
{
	if ( num==0 )
	{
		_this->data.push_back(0);
		return;
	}

	uint8_t  num4q = static_cast<uint8_t>(  num / 1000000 );
	uint32_t num4r = static_cast<uint32_t>( num - 1000000*num4q );
	uint8_t  num3q = static_cast<uint8_t>(  num4r / 10000 );
	uint32_t num3r = static_cast<uint32_t>( num4r - 10000*num3q );
	uint8_t  num2q = static_cast<uint8_t>(  num3r / 100 );
	uint8_t  num1q = static_cast<uint8_t>(  num3r - 100*num2q );

	_this->data.push_back(num1q);
	_this->data.push_back(num2q);
	_this->data.push_back(num3q);
	_this->data.push_back(num4q);

	for ( int i=3 ; i>0 ; i-- )
	{
		if ( _this->data[i]==0 )
		{
			_this->data.pop_back();
		}
		else
		{
			break;
		}
	}
}

static void SetSignedNumberToInt2(struct Int2Private *_this,int32_t num)
{
	_this->data.clear();

	if ( num==0 )
	{
		_this->negative = false;
		_this->data.push_back(0);
		return;
	}
	else if ( num<0 )
	{
		_this->negative = true;
		num *= -1;
	}
	else
	{
		_this->negative = false;
	}

	uint8_t  num4q = static_cast<uint8_t>( num / 1000000 );
	int32_t  num4r = static_cast<int32_t>( num - 1000000*num4q );
	uint8_t  num3q = static_cast<uint8_t>( num4r / 10000 );
	int32_t  num3r = static_cast<int32_t>( num4r - 10000*num3q );
	uint8_t  num2q = static_cast<uint8_t>( num3r / 100 );
	uint8_t  num1q = static_cast<uint8_t>( num3r - 100*num2q );

	_this->data.push_back(num1q);
	_this->data.push_back(num2q);
	_this->data.push_back(num3q);
	_this->data.push_back(num4q);

	for ( int i=3 ; i>0 ; i-- )
	{
		if ( _this->data[i]==0 )
		{
			_this->data.pop_back();
		}
		else
		{
			break;
		}
	}
}

Int2::Int2(int32_t num):_this(new struct Int2Private)
{
	SetSignedNumberToInt2(_this,num);
}

static uint8_t TwoCharStringToNumber(const char *str)
{
	int  num1 = str[1]-'0';
	int  num2 = str[0]-'0';

	num1 += num2*10;

	return static_cast<uint8_t>(num1);
}

static void StringToIntClass(const std::string &number,struct Int2Private *obj)
{
	NumberFormat report(number);

	if ( !report.isInteger() || !report.isDecimal() )
	{
		obj->data.push_back(0);
		toy::Oops(TOY_MARK);
		return;
	}

	const char* point = number.c_str();
	auto         size = number.size();

	if ( *point == '-' )
	{
		point++;
		size--;
		obj->negative = true;
	}

	if ( (size%2)==1 )
	{
		auto  temp = (size+1)/2;

		obj->data.resize(temp);
		obj->data[temp-1] = (*point)-'0';
		point++;
		size--;
	}
	else
	{
		obj->data.resize(size/2);
	}

	size = size/2;

	for ( auto i=size ; i>0 ; i--,point+=2)
	{
		obj->data[i-1] = TwoCharStringToNumber(point);
	}
}

Int2::Int2(std::string number):_this(new struct Int2Private)
{
	StringToIntClass(number,_this);
}

bool Int2::get(int8_t *number) const
{
	if ( _this->data.size()>2 )
	{
		return false;
	}

	int32_t   buffer = _this->data[0];

	if ( _this->data.size()==2 )
	{
		buffer += int32_t(_this->data[1]) * 100;
	}

	if ( _this->negative )
	{
		buffer *= -1;
	}

	if ( buffer>128 || buffer<-127 )
	{
		return false;
	}

	*number = static_cast<int8_t>(buffer);

	return true;
}

bool Int2::get(uint8_t *number) const
{
	if ( _this->negative )
	{
		return false;
	}

	if ( _this->data.size()>2 )
	{
		return false;
	}

	uint32_t   buffer = _this->data[0];

	if ( _this->data.size()==2 )
	{
		buffer += uint32_t(_this->data[1]) * 100;
	}

	if ( buffer>255 )
	{
		return false;
	}

	*number = static_cast<uint8_t>(buffer);

	return true;
}

static inline char NumberToChar(int num)
{
	char  ff = '0';

	return ff + num;
}

bool Int2::get(std::string *number) const
{
	if ( _this->data.size()>0 )
	{
		if ( _this->data.size()==1 && _this->data[0]==0 )
		{
			(*number) = "0";
			return true;
		}
	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	std::string &str = *number;

	if ( _this->negative )
	{
		str = "-";
	}
	else
	{
		str = "";
	}

	int  temp1 = 0;
	int  temp2 = 0;
	int  temp3 = 0;

	auto size = _this->data.size();
	bool nonZeroFound = false;

	for ( auto i=size ; i>0 ; i-- )
	{
		temp1 = _this->data[i-1];
		temp2 = temp1 / 10;
		temp3 = temp1 - temp2*10;

		if ( ! nonZeroFound )
		{
			auto char1 = NumberToChar(temp2);

			if ( char1!='0' )
			{
				nonZeroFound = true;
				str.push_back(char1);
			}
		}
		else
		{
			str.push_back(NumberToChar(temp2));
		}

		if ( ! nonZeroFound )
		{
			auto char2 = NumberToChar(temp3);

			if ( char2!='0' )
			{
				nonZeroFound = true;
				str.push_back(char2);
			}
		}
		else
		{
			str.push_back(NumberToChar(temp3));
		}
	}

	return true;
}

auto Int2::str() const -> const std::string
{
	std::string str;
	this->get(&str);
	return str;
}

auto Int2::divide(const Int2 &number) -> const Int2
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	if ( (*this)<number )
	{
		Int2  num = (*this);
		(*this) = 0;
		return num;
	}

	std::vector<uint8_t>  quotient;
	Int2                  residue;

	residue._this->negative = _this->negative;

	ArrayDivide(_this->data,number._this->data,&quotient,&(residue._this->data),99);

	_this->data.swap(quotient);  // _this->data = quotient;

	_this->negative = ( _this->negative != number._this->negative );

	return residue;
}

void Int2::operator /= (const Int2 &number)
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	this->divide(number);
}

void Int2::operator *= (const Int2 &number)
{
	if ( (*this)==0 ) return;

	if ( number==0 )
	{
		(*this) = 0;
		return;
	}

	_this->negative = ( _this->negative != number._this->negative );

	std::vector<uint8_t>  buffer( _this->data.size()+number._this->data.size() ,0);

	auto size1 = _this->data.size();
	auto size2 = number._this->data.size();

	uint32_t  temp  = 0;
	uint32_t  tempQ = 0;
	uint32_t  tempR = 0;

	for ( decltype(size2) i=0; i<size2 ; ++i)
	{
		for ( decltype(size1) j=0; j<size1 ; ++j)
		{
			temp = static_cast<uint32_t>(_this->data[j]) * static_cast<uint32_t>(number._this->data[i]);

			if ( temp>99 )
			{
				tempQ = temp / 100;
				tempR = temp - tempQ*100;
			}
			else
			{
				tempQ = 0;
				tempR = temp;
			}

			AddNumberToArray(&buffer,i+j  ,tempR,99);
			AddNumberToArray(&buffer,i+j+1,tempQ,99);
		}
	}

	CleanZeroEnd(&buffer);

	_this->data.swap(buffer);  // _this->data = buffer;
}

static void ByteAndByte(uint8_t a,uint8_t b,uint8_t *ans8bit,uint8_t *ans16bit)
{
	int  x = a;
	int  y = b;
	int  c = x+y;

	*ans16bit = c/100;
	*ans8bit  = c - 100 * (*ans16bit);
}

// ArrayA -= ArrayB
static void ArrayMinusEqualArray(std::vector<uint8_t> *arrayA,const std::vector<uint8_t> arrayB)
{
	uint32_t  size = arrayB.size();

	for ( uint32_t i=0 ; i<size ; i++ )
	{
		if ( (*arrayA)[i] < arrayB[i] )
		{
			for ( int j=1 ;  ; j++ )
			{
				if ( (*arrayA)[i+j] == 0 )
				{
					(*arrayA)[i+j] = 99;
				}
				else
				{
					(*arrayA)[i+j] -= 1;
					break;
				}
			}

			uint8_t   temp = 99;
			temp -= arrayB[i];
			(*arrayA)[i] = temp + (*arrayA)[i] + 1;
		}
		else
		{
			(*arrayA)[i] -= arrayB[i];
		}
	}
}

bool Int2::isAbsoluteValueBiggerThan(const Int2 &number)
{
	if ( CompareAbsoluteValue(_this->data,number._this->data)>0 )
	{
		return true;
	}

	return false;
}

bool Int2::isAbsoluteValueSmallerThan(const Int2 &number)
{
	if ( CompareAbsoluteValue(_this->data,number._this->data)<0 )
	{
		return true;
	}

	return false;
}

void Int2::operator += (const Int2 &number)
{
	if      ( _this->negative==true  && number._this->negative==true )
	{
		ArrayAndEqualArray(&(_this->data),number._this->data,&ByteAndByte);
	}
	else if ( _this->negative==false && number._this->negative==false )
	{
		ArrayAndEqualArray(&(_this->data),number._this->data,&ByteAndByte);
	}
	else if ( _this->negative==true  && number._this->negative==false )
	{
		if ( isAbsoluteValueBiggerThan(number) )
		{
			ArrayMinusEqualArray(&(_this->data),number._this->data);
		}
		else if ( isAbsoluteValueSmallerThan(number) )
		{
			std::vector<uint8_t>  data = _this->data;
			_this->data = number._this->data;
			ArrayMinusEqualArray(&(_this->data),data);
			_this->negative = number._this->negative;
		}
		else
		{
			_this->data.clear();
			_this->data.push_back(0);
		}
	}
	else if ( _this->negative==false && number._this->negative==true )
	{
		if ( isAbsoluteValueBiggerThan(number) )
		{
			ArrayMinusEqualArray(&(_this->data),number._this->data);
		}
		else if ( isAbsoluteValueSmallerThan(number) )
		{
			std::vector<uint8_t>  data = _this->data;
			_this->data = number._this->data;
			ArrayMinusEqualArray(&(_this->data),data);
			_this->negative = number._this->negative;
		}
		else
		{
			_this->data.clear();
			_this->data.push_back(0);
		}
	}
	else
	{
		toy::Oops(TOY_MARK);
	}

	CleanZeroEnd(&(_this->data));
}

void Int2::operator -= (const Int2 &number)
{
	_this->negative = ! _this->negative;
	*this += number;
	_this->negative = ! _this->negative;
}

auto Int2::operator + (const Int2 &number) const -> const Int2
{
	Int2  result(*this);
	result += number;
	return result;
}

auto Int2::operator - (const Int2 &number) const -> const Int2
{
	Int2  result(*this);
	result -= number;
	return result;
}

auto Int2::operator * (const Int2 &number) const -> const Int2
{
	Int2  result(*this);
	result *= number;
	return result;
}

auto Int2::operator / (const Int2 &number) const -> const Int2
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	std::vector<uint8_t>  residue;
	Int2                  quotient;

	ArrayDivide(_this->data,number._this->data,&(quotient._this->data),&residue,99);

	quotient._this->negative = ( _this->negative != number._this->negative );

	return quotient;
}

auto Int2::operator % (const Int2 &number) const -> const Int2
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	Int2                  residue;
	std::vector<uint8_t>  quotient;

	ArrayDivide(_this->data,number._this->data,&quotient,&(residue._this->data),99);

	residue._this->negative = _this->negative;

	return residue;
}

void Int2::operator %= (const Int2 &number)
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	std::vector<uint8_t>  residue;
	std::vector<uint8_t>  quotient;

	ArrayDivide(_this->data,number._this->data,&quotient,&residue,99);

	_this->data.swap(residue);
}

void Int2::operator = (const Int2 &number)
{
	*_this = *(number._this);
}

void Int2::operator = (std::string number)
{
	_this->data.clear();
	StringToIntClass(number,_this);
}

void Int2::operator = (int32_t number)
{
	SetSignedNumberToInt2(_this,number);
}

static int CompareWithInt32(const struct Int2Private *_this,int32_t num)
{
	auto size = _this->data.size();

	if ( (size==1)&&(_this->data[0]==0) )
	{
		if ( num==0 )
			return 0;
		else if ( num<0 )
			return 1;
		else if ( num>0 )
			return -1;
	}

	if ( num==0 )
	{
		if ( _this->negative )
			return -1;
		else
			return 1;
	}

	if ( size>5 )
	{
		if ( _this->negative )
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	if ( size==5 )
	{
		if ( _this->data[4]>21 )
		{
			if ( _this->negative )
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}

	uint32_t  number_uint = 0;

	{
		uint32_t  buffer = 0;
		uint32_t  base = 1;

		for (decltype(size) i=0;i<size;i++)
		{
			buffer = _this->data[i];
			number_uint += buffer * base;
			base *= 100;
		}
	}

	int32_t  number = 0;

	// int32_t  Max:2147483647
	if ( number_uint>2147483647 )
	{
		if ( _this->negative )
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		number = static_cast<int32_t>(number_uint);
	}

	if ( _this->negative )
	{
		number *= -1;
	}

	if ( number>num )
	{
		return 1;
	}
	else if ( number==num )
	{
		return 0;
	}

	return -1;
}

bool Int2::operator > (int32_t num) const
{
	if ( CompareWithInt32(_this,num)==1 )
	{
		return true;
	}

	return false;
}

bool Int2::operator < (int32_t num) const
{
	if ( CompareWithInt32(_this,num)==-1 )
	{
		return true;
	}

	return false;
}

bool Int2::operator == (int32_t num) const
{
	if ( CompareWithInt32(_this,num)==0 )
	{
		return true;
	}

	return false;
}

bool Int2::operator >= (int32_t num) const
{
	return ! ( (*this)<num );
}

bool Int2::operator <= (int32_t num) const
{
	return ! ( (*this)>num );
}

bool Int2::operator > (const Int2 &number) const
{
	if (         _this->data.size() == 1 &&
	      number._this->data.size() == 1 &&
	             _this->data[0]     == 0 &&
	      number._this->data[0]     == 0 )
	{
		return false;
	}

	if ( _this->negative==true  && number._this->negative==false )
	{
		return false;
	}

	if ( _this->negative==false && number._this->negative==true )
	{
		return true;
	}

	auto res = CompareAbsoluteValue(_this->data,number._this->data);

	if ( res==0 )
	{
		return false;
	}

	if ( _this->negative==false && res==1 )
	{
		return true;
	}

	if ( _this->negative==true && res==-1 )
	{
		return true;
	}

	return false;
}

bool Int2::operator < (const Int2 &number) const
{
	if (         _this->data.size() == 1 &&
	      number._this->data.size() == 1 &&
	             _this->data[0]     == 0 &&
	      number._this->data[0]     == 0 )
	{
		return false;
	}

	if ( _this->negative==true  && number._this->negative==false )
	{
		return true;
	}

	if ( _this->negative==false && number._this->negative==true )
	{
		return false;
	}

	auto res = CompareAbsoluteValue(_this->data,number._this->data);

	if ( res==0 )
	{
		return false;
	}

	if ( _this->negative==false && res==-1 )
	{
		return true;
	}

	if ( _this->negative==true && res==1 )
	{
		return true;
	}

	return false;
}

bool Int2::operator == (const Int2 &number) const
{
	if (         _this->data.size() == 1 &&
	      number._this->data.size() == 1 &&
	             _this->data[0]     == 0 &&
	      number._this->data[0]     == 0 )
	{
		return true;
	}

	auto res = CompareAbsoluteValue(_this->data,number._this->data);

	if ( res==0 )
	{
		if ( _this->negative == number._this->negative )
		{
			return true;
		}
	}

	return false;
}

bool Int2::operator != (const Int2 &number) const
{
	return (*this)==number ? false : true;
}

bool Int2::operator >= (const Int2 &number) const
{
	return ! ( (*this)<number );
}

bool Int2::operator <= (const Int2 &number) const
{
	return ! ( (*this)>number );
}
