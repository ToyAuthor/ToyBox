#include <vector>
#include <memory>
#include <cstring>
#include <limits>
#include "toy/Exception.hpp"
#include "toy/Log.hpp"
#include "toy/math/Int.hpp"
#include "toy/math/Int2.hpp"
#include "toy/math/NumberFormat.hpp"
#include "toy/math/IntCommon.hpp"

namespace toy{
namespace math{

struct IntPrivate
{
	std::vector<uint8_t>  data;  // Unsigned little endian.
	bool                  negative = false;
};

}}

using namespace toy;
using namespace math;

Int::~Int()
{
	delete _this;
}

void Int::setRawData(const uint8_t* ptr, uint32_t size, bool isNegative)
{
	_this->data.resize(size);
	std::memcpy((void*)_this->data.data(),(void*)ptr,size);
	_this->negative = isNegative;
}

bool Int::negative() const
{
	return _this->negative;
}

const uint8_t* Int::data() const
{
	return _this->data.data();
}

uint32_t Int::size() const
{
	#if TOY_OPTION_CHECK
		if ( sizeof(std::vector<uint8_t>::size_type)>sizeof(uint32_t) )
		{
			if ( _this->data.size() > static_cast<std::vector<uint8_t>::size_type>(std::numeric_limits<uint32_t>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	return _this->data.size();
}

Int::Int():_this(new struct IntPrivate)
{
	_this->data.push_back(0);
}

Int::Int(const Int &number):_this(new struct IntPrivate)
{
	*_this = *(number._this);
}

Int::Int(int8_t number):_this(new struct IntPrivate)
{
	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	_this->data.push_back(number);
}

Int::Int(uint8_t number):_this(new struct IntPrivate)
{
	_this->data.push_back(number);
}

Int::Int(int16_t number):_this(new struct IntPrivate)
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

	int16_t  temp = number%0x100;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - temp)>>8);
}

Int::Int(uint16_t number):_this(new struct IntPrivate)
{
	if ( number==0 )
	{
		_this->data.push_back(0);
		return;
	}

	uint16_t  temp = number%0x100;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - temp)>>8);
}

Int::Int(int32_t number):_this(new struct IntPrivate)
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

	int32_t  temp = number%0x100;
	int32_t  temp2;
	_this->data.push_back( temp);                if ( temp==number ) return; temp2 = temp; temp = number%0x10000;
	_this->data.push_back((temp   - temp2)>>8 ); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000;
	_this->data.push_back((temp   - temp2)>>16); if ( temp==number ) return;
	_this->data.push_back((number - temp )>>24);
}

Int::Int(uint32_t number):_this(new struct IntPrivate)
{
	if ( number==0 )
	{
		_this->data.push_back(0);
		return;
	}

	uint32_t  temp = number%0x100;
	uint32_t  temp2;
	_this->data.push_back( temp);                if ( temp==number ) return; temp2 = temp; temp = number%0x10000;
	_this->data.push_back((temp   - temp2)>>8 ); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000;
	_this->data.push_back((temp   - temp2)>>16); if ( temp==number ) return;
	_this->data.push_back((number - temp )>>24);
}

Int::Int(int64_t number):_this(new struct IntPrivate)
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

	int64_t  temp = number%0x100;
	int64_t  temp2;
	_this->data.push_back( temp);                if ( temp==number ) return; temp2 = temp; temp = number%0x10000;
	_this->data.push_back((temp   - temp2)>>8 ); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000;
	_this->data.push_back((temp   - temp2)>>16); if ( temp==number ) return; temp2 = temp; temp = number%0x100000000;
	_this->data.push_back((temp   - temp2)>>24); if ( temp==number ) return; temp2 = temp; temp = number%0x10000000000;
	_this->data.push_back((temp   - temp2)>>32); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000000000;
	_this->data.push_back((temp   - temp2)>>40); if ( temp==number ) return; temp2 = temp; temp = number%0x100000000000000;
	_this->data.push_back((temp   - temp2)>>48); if ( temp==number ) return;
	_this->data.push_back((number - temp )>>56);
}

Int::Int(uint64_t number):_this(new struct IntPrivate)
{
	if ( number==0 )
	{
		_this->data.push_back(0);
		return;
	}

	uint64_t  temp = number%0x100;
	uint64_t  temp2;
	_this->data.push_back( temp);                if ( temp==number ) return; temp2 = temp; temp = number%0x10000;
	_this->data.push_back((temp   - temp2)>>8 ); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000;
	_this->data.push_back((temp   - temp2)>>16); if ( temp==number ) return; temp2 = temp; temp = number%0x100000000;
	_this->data.push_back((temp   - temp2)>>24); if ( temp==number ) return; temp2 = temp; temp = number%0x10000000000;
	_this->data.push_back((temp   - temp2)>>32); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000000000;
	_this->data.push_back((temp   - temp2)>>40); if ( temp==number ) return; temp2 = temp; temp = number%0x100000000000000;
	_this->data.push_back((temp   - temp2)>>48); if ( temp==number ) return;
	_this->data.push_back((number - temp )>>56);
}

static auto FindTheCloseOneBase256(const Int2 &target)->std::shared_ptr<std::vector<Int2>>
{
	auto ptr = std::make_shared<std::vector<Int2>>();

	if ( target<256)
	{
		ptr->push_back(Int2("256"));
		return ptr;
	}

	Int2   base("1");

	do
	{
		base *= 256;
		ptr->push_back(base);
	}
	while( target>=base );

	return ptr;
}

static void StringToNumber(const char *str,int size,std::vector<uint8_t> *data)
{
	std::vector<uint8_t> buffer;

	Int2      num(std::string(str,size));
	auto      baseList = FindTheCloseOneBase256(num);
	Int2      bb;
	uint8_t   temp;
	Int2      temp1;

	#if TOY_OPTION_CHECK
		if ( sizeof(std::vector<Int2>::size_type)>=sizeof(int) )
		{
			if ( baseList->size() > static_cast<std::vector<Int2>::size_type>(std::numeric_limits<int>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	for ( int i = baseList->size()-1 ; i>=0 ; i-- )
	{
		bb = (*baseList)[i];
		temp1 = num;
		num = temp1.divide(bb);
		temp1.get(&temp);
		buffer.push_back(temp);

		if (i==0)
		{
			num.get(&temp);
			buffer.push_back(temp);
		}
	}

	#if TOY_OPTION_CHECK
		if ( sizeof(std::vector<uint8_t>::size_type)>=sizeof(int) )
		{
			if ( buffer.size() > static_cast<std::vector<uint8_t>::size_type>(std::numeric_limits<int>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	for ( int i = buffer.size()-1 ; i>=0 ; i-- )
	{
		data->push_back(buffer[i]);
	}

	CleanZeroEnd(data);
}

static inline uint8_t CharToNumber(const char ch)
{
	return ch-'0';
}

static uint8_t HexCharToNumber(const char ch)
{
	if ( ch>'9' )
	{
		switch ( ch )
		{
			case 'a': return 10;
			case 'A': return 10;
			case 'b': return 11;
			case 'B': return 11;
			case 'c': return 12;
			case 'C': return 12;
			case 'd': return 13;
			case 'D': return 13;
			case 'e': return 14;
			case 'E': return 14;
			case 'f': return 15;
			case 'F': return 15;
			default:
				toy::Oops(TOY_MARK);
		}
	}
	else
	{
		return CharToNumber(ch);
	}

	return 0;
}

static void HexStringToNumber(const char *str,int size,std::vector<uint8_t> *data)
{
	bool isFull = true;
	const char *num = str + (size-1);

	for ( ; size>0 ;num--,size--)
	{
		if ( isFull )
		{
			isFull = false;
			data->push_back(HexCharToNumber(*num));
		}
		else
		{
			isFull = true;
			uint8_t  temp = data->back();
			temp += (HexCharToNumber(*num)<<4);
			(*data)[data->size()-1] = temp;
		}
	}

	#if TOY_OPTION_CHECK
		if ( data->back()==uint8_t(0) )
		{
			toy::Oops(TOY_MARK);
		}
	#endif
}

static void StringToIntClass(const std::string &number,struct IntPrivate *obj)
{
	NumberFormat  report(number);

	const char* point = number.c_str();
	int   size = number.size();

	if ( report.isInteger() )
	{
		if ( report.isNegative() )
		{
			obj->negative = true;
			point = point+1;
			size--;
		}

		if ( report.isHexadecimal() )
		{
			point = point+2;
			size = size - 2;
			HexStringToNumber(point,size,&(obj->data));
			return;
		}
		else if ( report.isDecimal() )
		{
			StringToNumber(point,size,&(obj->data));
			return;
		}
	}

	toy::Oops(TOY_MARK);
	obj->data.push_back(0);
}

Int::Int(std::string number):_this(new struct IntPrivate)
{
	StringToIntClass(number,_this);
}

bool Int::get(int8_t *number) const
{
	if ( _this->data.size()>1 )
	{
		return false;
	}

	if ( _this->data[0]>127 )
	{
		return false;
	}

	*number = _this->data[0];

	if ( _this->negative )
	{
		*number *= -1;
	}

	return true;
}

bool Int::get(uint8_t *number) const
{
	if ( _this->data.size()>1 )
	{
		return false;
	}

	if ( _this->negative )
	{
		return false;
	}

	*number = _this->data[0];

	return true;
}

bool Int::get(int16_t *number) const
{
	if ( _this->data.size()>2 )
	{
		return false;
	}

	if ( _this->data[1]>127 )
	{
		return false;
	}

	int16_t  temp = _this->data[0];
	*number  = temp;     temp = _this->data[1];
	*number += temp<<8;

	if ( _this->negative )
	{
		*number *= -1;
	}

	return true;
}

bool Int::get(uint16_t *number) const
{
	if ( _this->data.size()>2 )
	{
		return false;
	}

	if ( _this->negative )
	{
		return false;
	}

	uint16_t  temp = _this->data[0];
	*number  = temp;     temp = _this->data[1];
	*number += temp<<8;

	return true;
}

bool Int::get(int32_t *number) const
{
	if ( _this->data.size()>4 )
	{
		return false;
	}

	if ( _this->data[3]>127 )
	{
		return false;
	}

	int32_t  temp = _this->data[0];
	*number  = temp;     temp = _this->data[1];
	*number += temp<<8;  temp = _this->data[2];
	*number += temp<<16; temp = _this->data[3];
	*number += temp<<24;

	if ( _this->negative )
	{
		*number *= -1;
	}

	return true;
}

bool Int::get(uint32_t *number) const
{
	if ( _this->data.size()>4 )
	{
		return false;
	}

	if ( _this->negative )
	{
		return false;
	}

	uint32_t  temp = _this->data[0];
	*number  = temp;     temp = _this->data[1];
	*number += temp<<8;  temp = _this->data[2];
	*number += temp<<16; temp = _this->data[3];
	*number += temp<<24;

	return true;
}

bool Int::get(int64_t *number) const
{
	if ( _this->data.size()>8 )
	{
		return false;
	}

	if ( _this->data[7]>127 )
	{
		return false;
	}

	int64_t  temp = _this->data[0];
	*number  = temp;     temp = _this->data[1];
	*number += temp<<8;  temp = _this->data[2];
	*number += temp<<16; temp = _this->data[3];
	*number += temp<<24; temp = _this->data[4];
	*number += temp<<32; temp = _this->data[5];
	*number += temp<<40; temp = _this->data[6];
	*number += temp<<48; temp = _this->data[7];
	*number += temp<<56;

	if ( _this->negative )
	{
		*number *= -1;
	}

	return true;
}

bool Int::get(uint64_t *number) const
{
	if ( _this->data.size()>8 )
	{
		return false;
	}

	if ( _this->negative )
	{
		return false;
	}

	uint64_t  temp = _this->data[0];
	*number  = temp;     temp = _this->data[1];
	*number += temp<<8;  temp = _this->data[2];
	*number += temp<<16; temp = _this->data[3];
	*number += temp<<24; temp = _this->data[4];
	*number += temp<<32; temp = _this->data[5];
	*number += temp<<40; temp = _this->data[6];
	*number += temp<<48; temp = _this->data[7];
	*number += temp<<56;

	return true;
}

static inline void AddNumberTo32bitArray(std::vector<uint32_t> *nbuffer,uint32_t num)
{
	if ( nbuffer->size()==0 )
	{
		nbuffer->push_back(num);
		return;
	}

	(*nbuffer)[0] += num;

	#if TOY_OPTION_CHECK
		if ( sizeof(std::vector<uint32_t>::size_type)>=sizeof(int) )
		{
			if ( nbuffer->size() > static_cast<std::vector<uint32_t>::size_type>(std::numeric_limits<int>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	int size = nbuffer->size();

	for ( int i=0 ; i<size-1 ; i++ )
	{
		if ( (*nbuffer)[i]>999999999 )
		{
			auto  temp = ((*nbuffer)[i])%1000000000;
			(*nbuffer)[i+1] += ((*nbuffer)[i] - temp)/1000000000;
			(*nbuffer)[i] = temp;
		}
		else
		{
			return;
		}
	}

	if ( (*nbuffer)[size-1]>999999999 )
	{
		auto  temp = ((*nbuffer)[size-1])%1000000000;
		nbuffer->push_back(((*nbuffer)[size-1] - temp)/1000000000);
		(*nbuffer)[size-1] = temp;
	}
}

static inline void CalRealNumber(const uint32_t& num,uint32_t deep,std::vector<uint32_t> *nbuffer)
{
	if ( deep==1 )
	{
		AddNumberTo32bitArray(nbuffer,num*256);
	}
	else
	{
		for ( int i=256 ; i>0 ; i-- )
		{
			CalRealNumber(num,deep-1,nbuffer);
		}
	}
}

static inline void NumberToString(char *str,uint32_t num)
{
	char  ff = '0';

	uint32_t  bu[10] = {0};
	uint32_t  temp1 = num%100;
	uint32_t  temp2 = num%10;

	bu[8] = temp2;
	bu[7] = (temp1 - temp2)/10;       temp2 = num%1000;
	bu[6] = (temp2 - temp1)/100;      temp1 = num%10000;
	bu[5] = (temp1 - temp2)/1000;     temp2 = num%100000;
	bu[4] = (temp2 - temp1)/10000;    temp1 = num%1000000;
	bu[3] = (temp1 - temp2)/100000;   temp2 = num%10000000;
	bu[2] = (temp2 - temp1)/1000000;  temp1 = num%100000000;
	bu[1] = (temp1 - temp2)/10000000; temp2 = num%1000000000;
	bu[0] = (temp2 - temp1)/100000000;

	str[8] = ff + bu[8];
	str[7] = ff + bu[7];
	str[6] = ff + bu[6];
	str[5] = ff + bu[5];
	str[4] = ff + bu[4];
	str[3] = ff + bu[3];
	str[2] = ff + bu[2];
	str[1] = ff + bu[1];
	str[0] = ff + bu[0];
	str[9] = '\0';
}

static inline int GetNotZeroIndex(char *str)
{
	for ( int i=0 ; i<9 ; i++ )
	{
		if ( str[i] != '0' )
		{
			return i;
		}
	}

	return 0;
}

bool Int::get(std::string *number) const
{
	std::vector<uint32_t>   nbuffer;

	if ( _this->data.size()>0 )
	{
		if ( _this->data.size()==1 && _this->data[0]==0 )
		{
			(*number) = "0";
			return true;
		}

		AddNumberTo32bitArray(&nbuffer,_this->data[0]);
	}
	else
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	#if TOY_OPTION_CHECK
		if ( sizeof(std::vector<uint8_t>::size_type)>sizeof(uint32_t) )
		{
			if ( _this->data.size() > static_cast<std::vector<uint8_t>::size_type>(std::numeric_limits<uint32_t>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	uint32_t size = _this->data.size();

	for ( uint32_t i=1 ; i<size ; i++ )
	{
		CalRealNumber(_this->data[i],i,&nbuffer);
	}

	std::string   &str = *number;

	str = "";

	if ( _this->negative )
	{
		str += "-";
	}

	char   cbuffer[10] = {'\0'};

	NumberToString(cbuffer,nbuffer[nbuffer.size()-1]);
	str += (cbuffer + GetNotZeroIndex(cbuffer));

	#if TOY_OPTION_CHECK
		if ( sizeof(std::vector<uint32_t>::size_type)>sizeof(int32_t) )
		{
			if ( nbuffer.size() > static_cast<std::vector<uint32_t>::size_type>(std::numeric_limits<int32_t>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	for ( int32_t i=nbuffer.size()-2 ; i>=0 ; i-- )
	{
		NumberToString(cbuffer,nbuffer[i]);
		str += cbuffer;
	}

	return true;
}

static char BinaryToChar(uint8_t num)
{
	#if TOY_OPTION_CHECK
		if ( num>15 )
		{
			toy::Oops(TOY_MARK);
			return '0';
		}
	#endif

	if ( num>9 )
	{
		return 'a' + static_cast<char>(num-10);
	}
	else
	{
		return '0' + static_cast<char>(num);
	}
}

static char* BinaryToString(uint8_t num,char *buffer)
{
	uint8_t  temp1 = num%0x10;
	uint8_t  temp2 = (num - temp1)>>4;

	buffer[0] = BinaryToChar(temp2);
	buffer[1] = BinaryToChar(temp1);

	return buffer;
}

bool Int::getHex(std::string *number) const
{
	number->clear();

	if ( (*this)==0 )
	{
		*number += "0x0";
		return true;
	}

	if ( _this->negative )
	{
		*number += "-";
	}

	*number += "0x";

	char  buffer[3] = {'\0'};

	*number += BinaryToString(_this->data.back(),buffer);

	if ( buffer[0]=='0' )
	{
		auto i = number->size();
		(*number)[i-2] = (*number)[i-1];
		number->pop_back();
	}

	if ( _this->data.size()==1 ) return true;

	for ( auto i = _this->data.size()-1 ; i>0 ; i-- )
	{
		*number += BinaryToString(_this->data[i-1],buffer);
	}

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

void Int::operator = (const Int &number)
{
	*_this = *(number._this);
}

void Int::operator = (int8_t number)  { (*_this) = *(Int(number)._this); }
void Int::operator = (uint8_t number) { (*_this) = *(Int(number)._this); }
void Int::operator = ( int16_t number){ (*_this) = *(Int(number)._this); }
void Int::operator = (uint16_t number){ (*_this) = *(Int(number)._this); }
void Int::operator = ( int32_t number){ (*_this) = *(Int(number)._this); }
void Int::operator = (uint32_t number){ (*_this) = *(Int(number)._this); }
void Int::operator = ( int64_t number){ (*_this) = *(Int(number)._this); }
void Int::operator = (uint64_t number){ (*_this) = *(Int(number)._this); }

void Int::operator = (std::string number)
{
	_this->data.clear();
	StringToIntClass(number,_this);
}

bool Int::isAbsoluteValueBiggerThan(const Int &number)
{
	if ( CompareAbsoluteValue(_this->data,number._this->data)>0 )
	{
		return true;
	}

	return false;
}

bool Int::isAbsoluteValueSmallerThan(const Int &number)
{
	if ( CompareAbsoluteValue(_this->data,number._this->data)<0 )
	{
		return true;
	}

	return false;
}

static void ByteAndByte(uint8_t a,uint8_t b,uint8_t *ans8bit,uint8_t *ans16bit)
{
	int  x = a;
	int  y = b;
	int  c = x+y;

	*ans8bit  = c%0x100;
	*ans16bit = (c-*ans8bit)>>8;
}

// ArrayA -= ArrayB
static void ArrayMinusEqualArray(std::vector<uint8_t> *arrayA,const std::vector<uint8_t>& arrayB)
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
					(*arrayA)[i+j] = 0xFF;
				}
				else
				{
					(*arrayA)[i+j] -= 1;
					break;
				}
			}

			uint8_t   temp = 0xFF;
			temp -= arrayB[i];
			(*arrayA)[i] = temp + (*arrayA)[i] + 1;
		}
		else
		{
			(*arrayA)[i] -= arrayB[i];
		}
	}
}

void Int::operator +=(const Int &number)
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

auto Int::operator + (const Int &number) const -> const Int
{
	Int  result(*this);
	result += number;
	return result;
}

void Int::operator -=(const Int &number)
{
	_this->negative = ! _this->negative;
	*this += number;
	_this->negative = ! _this->negative;
}

auto Int::operator - (const Int &number) const -> const Int
{
	Int  result(*this);
	result -= number;
	return result;
}

void Int::operator *= (const Int &number)
{
	if ( (*this)==(int32_t)0 ) return;

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

	for ( decltype(size2) i=0; i<size2 ; i++)
	{
		for ( decltype(size1) j=0; j<size1 ; j++)
		{
			temp = static_cast<uint32_t>(_this->data[j]) * static_cast<uint32_t>(number._this->data[i]);

			if ( temp>255 )
			{
				tempQ = temp >> 8;
				tempR = temp - (tempQ<<8);
			}
			else
			{
				tempQ = 0;
				tempR = temp;
			}

			AddNumberToArray(&buffer,i+j  ,tempR,255);
			AddNumberToArray(&buffer,i+j+1,tempQ,255);
		}
	}

	CleanZeroEnd(&buffer);

	_this->data.swap(buffer);  // _this->data = buffer;
}

auto Int::operator * (const Int &number) const -> const Int
{
	Int  result(*this);
	result *= number;
	return result;
}

auto Int::divide(const Int &number) -> const Int
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	std::vector<uint8_t>  quotient;
	Int                   residue;

	residue._this->negative = _this->negative;

	ArrayDivide(_this->data,number._this->data,&quotient,&(residue._this->data),255);

	_this->data.swap(quotient);  // _this->data = quotient;

	_this->negative = ( _this->negative != number._this->negative );

	return residue;
}

void Int::operator /= (const Int &number)
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	this->divide(number);
}

auto Int::operator / (const Int &number) const -> const Int
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	std::vector<uint8_t>  residue;
	Int                   quotient;

	ArrayDivide(_this->data,number._this->data,&(quotient._this->data),&residue,255);

	quotient._this->negative = ( _this->negative != number._this->negative );

	return quotient;
}

void Int::operator %= (const Int &number)
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	std::vector<uint8_t>  residue;
	std::vector<uint8_t>  quotient;

	ArrayDivide(_this->data,number._this->data,&quotient,&residue,255);

	_this->data.swap(residue);
}

auto Int::operator % (const Int &number) const -> const Int
{
	if ( number==0 )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	Int                   residue;
	std::vector<uint8_t>  quotient;

	ArrayDivide(_this->data,number._this->data,&quotient,&(residue._this->data),255);

	residue._this->negative = _this->negative;

	return residue;
}

auto Int::operator ^ (const Int &number) const -> const Int
{
	if ( number==0 )
	{
		return Int(1);
	}

	if ( number==1 )
	{
		return *this;
	}

	if ( number.negative() )
	{
		toy::Oops(TOY_MARK);
		return *this;
	}

	Int i      = number-1;
	Int result = *this;

	while ( i>0 )
	{
		result *= (*this);
		i = i-1;
	}

	return result;
}

void Int::operator ^=(const Int &number)
{
	*this = (*this)^number;
}

// Return value:
//     1 :this  > num
//     -1:this  < num
//     0 :this == num
static int CompareWithInt32(const struct IntPrivate *_this,const int32_t num)
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

	if ( size>4 )
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

	if ( size==4 && _this->data[3]>127 )
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

	int number = 0;

	{
		int  buffer = 0;
		int  base = 0;

		for (decltype(size) i=0;i<size;i++)
		{
			buffer = _this->data[i];
			number += buffer<< base;
			base += 8;
		}
	}

	if ( _this->negative )
	{
		number *= -1;
	}

	if ( number>num )
	{
		return 1;
	}
	else if ( number<num )
	{
		return -1;
	}

	return 0;
}

bool Int::operator ==(int32_t num) const
{
	if ( CompareWithInt32(_this,num)==0 )
	{
		return true;
	}

	return false;
}

bool Int::operator !=(int32_t num) const
{
	if ( CompareWithInt32(_this,num)==0 )
	{
		return false;
	}

	return true;
}

bool Int::operator >(int32_t num) const
{
	if ( CompareWithInt32(_this,num)==1 )
	{
		return true;
	}

	return false;
}

bool Int::operator <(int32_t num) const
{
	if ( CompareWithInt32(_this,num)==-1 )
	{
		return true;
	}

	return false;
}

bool Int::operator >=(int32_t num) const
{
	if ( CompareWithInt32(_this,num)>-1 )
	{
		return true;
	}

	return false;
}

bool Int::operator <=(int32_t num) const
{
	if ( CompareWithInt32(_this,num)<1 )
	{
		return true;
	}

	return false;
}

bool Int::operator > (const Int &number) const
{
	if (         _this->data.size() == 1 &&
	      number._this->data.size() == 1 &&
	             _this->data[0]     == 0 &&
	      number._this->data[0]     == 0 )
	{
		return false;
	}

	if ( _this->negative==false && number._this->negative==true )
	{
		return true;
	}

	if ( _this->negative==true  && number._this->negative==false )
	{
		return false;
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

bool Int::operator < (const Int &number) const
{
	if (         _this->data.size() == 1 &&
	      number._this->data.size() == 1 &&
	             _this->data[0]     == 0 &&
	      number._this->data[0]     == 0 )
	{
		return false;
	}

	if ( _this->negative==false && number._this->negative==true )
	{
		return false;
	}

	if ( _this->negative==true  && number._this->negative==false )
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
		return false;
	}

	if ( _this->negative==true && res==-1 )
	{
		return false;
	}

	return true;
}

bool Int::operator <=(const Int &number) const
{
	return !( *this > number );
}

bool Int::operator >=(const Int &number) const
{
	return !( *this < number );
}

bool Int::operator == (const Int &number) const
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

bool Int::operator !=(const Int &number) const
{
	return (*this)==number ? false : true;
}
