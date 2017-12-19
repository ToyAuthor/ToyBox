#include <vector>
#include <cstring>
#include "toy/math/Real.hpp"

namespace toy{
namespace math{

struct RealPrivate
{
	std::vector<uint8_t>  data;
//	std::vector<uint8_t>  divisor;
	bool                  negative = false;
};

}}

using namespace toy;
using namespace math;

Real::~Real()
{
	delete _this;
}

Real::Real(const Real &number):_this(new struct RealPrivate)
{
	*_this = *(number._this);
}

Real::Real(int8_t number):_this(new struct RealPrivate)
{
	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	_this->data.push_back(number);
}

Real::Real(uint8_t number):_this(new struct RealPrivate)
{
	_this->data.push_back(number);
}

Real::Real(int16_t number):_this(new struct RealPrivate)
{
	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	int16_t  temp = number%0x100;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - temp)>>8);
}

Real::Real(uint16_t number):_this(new struct RealPrivate)
{
	uint16_t  temp = number%0x100;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - temp)>>8);
}

Real::Real(int32_t number):_this(new struct RealPrivate)
{
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

Real::Real(uint32_t number):_this(new struct RealPrivate)
{
	uint32_t  temp = number%0x100;
	int32_t  temp2;
	_this->data.push_back( temp);                if ( temp==number ) return; temp2 = temp; temp = number%0x10000;
	_this->data.push_back((temp   - temp2)>>8 ); if ( temp==number ) return; temp2 = temp; temp = number%0x1000000;
	_this->data.push_back((temp   - temp2)>>16); if ( temp==number ) return;
	_this->data.push_back((number - temp )>>24);
}

Real::Real(int64_t number):_this(new struct RealPrivate)
{
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

Real::Real(uint64_t number):_this(new struct RealPrivate)
{
	uint64_t  temp = number%0x100;
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

template<typename T>
inline static void CopyArrayToReal(struct RealPrivate *member,const T *number, int datasize)
{
	member->data.resize(datasize);

	std::memcpy( static_cast<void*>(member->data.data()),
	             static_cast<const void*>(number),
	             datasize );
}

Real::Real(const int8_t *number, int datasize,bool negative):_this(new struct RealPrivate)
{
	_this->negative = negative;

	CopyArrayToReal(_this,number,datasize);
}

Real::Real(const uint8_t *number, int datasize,bool negative):_this(new struct RealPrivate)
{
	_this->negative = negative;

	CopyArrayToReal(_this,number,datasize);
}

bool Real::get(int8_t *number) const
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

bool Real::get(uint8_t *number) const
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

bool Real::get(int16_t *number) const
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

bool Real::get(uint16_t *number) const
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

bool Real::get(int32_t *number) const
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

bool Real::get(uint32_t *number) const
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

bool Real::get(int64_t *number) const
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

bool Real::get(uint64_t *number) const
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

inline static void AddNumberToArray(std::vector<int> *nbuffer,int num)
{
	if ( nbuffer->size()==0 )
	{
		nbuffer->push_back(num);
		return;
	}

	(*nbuffer)[0] += num;

	int size = nbuffer->size();

	for ( int i=0 ; i<size-1 ; i++ )
	{
		if ( (*nbuffer)[i]>999999999 )
		{
			auto  temp = ((*nbuffer)[i])%1000000000;
			(*nbuffer)[i+1] += ((*nbuffer)[i] - temp)/1000000000;
			(*nbuffer)[i] = temp;
			return;
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

inline static void CalRealNumber(const int index,int deep,std::vector<int> *nbuffer,const std::vector<uint8_t>& data)
{
	for ( int i=256 ; i>0 ; i-- )
	{
		if ( deep==1 )
		{
			AddNumberToArray(nbuffer,data[index]);
		}
		else
		{
			CalRealNumber(index,deep-1,nbuffer,data);
		}
	}
}

inline static void NumberToString(char *str,int num)
{
	char  ff = '0';

	int  bu[10] = {0};
	int  temp1 = num%100;
	int  temp2 = num%10;

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

inline static int GetNotZeroIndex(char *str)
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

bool Real::get(std::string *number) const
{
	std::vector<int>   nbuffer;

	if ( _this->data.size()>0 )
	{
		if ( _this->data.size()==1 && _this->data[0]==0 )
		{
			(*number) = "0";
			return true;
		}

		AddNumberToArray(&nbuffer,_this->data[0]);
	}
	else
	{
		return false;
	}

	uint32_t size = _this->data.size();

	for ( uint32_t i=1 ; i<size ; i++ )
	{
		CalRealNumber(i,i,&nbuffer,_this->data);
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

	for ( int i=nbuffer.size()-2 ; i>=0 ; i-- )
	{
		NumberToString(cbuffer,nbuffer[i]);
		str += cbuffer;
	}

	return true;
}

// [1,2,3,0,0,0,0,0] -> [1,2,3]
// [0,0,0,0,0] -> [0]
inline static void CleanZeroEnd(std::vector<uint8_t> *array)
{
	while ( array->back()==0 )
	{
		array->pop_back();

		if ( array->size()==0 )
		{
			array->push_back(0);
			break;
		}
	}
}

inline static void SetEnoughSize(std::vector<uint8_t> *array,uint32_t size)
{
	uint32_t   asize = array->size();

	if ( asize<size )
	{
		size -= asize;

		for ( uint32_t i=0; i<size ; i++ )
		{
			array->push_back(0);
		}
	}

	array->push_back(0);
}

inline static void ByteAndByte(uint8_t a,uint8_t b,uint8_t *ans8bit,uint8_t *ans16bit)
{
	int  x = a;
	int  y = b;
	int  c = x+y;

	*ans8bit  = c%0x100;
	*ans16bit = (c-*ans8bit)>>8;
}

// ArrayA += ArrayB
static void ArrayAndEqualArray(std::vector<uint8_t> *arrayA,const std::vector<uint8_t> arrayB)
{
	SetEnoughSize(arrayA,arrayB.size());

	uint8_t   temp1 = 0;
	uint8_t   temp2 = 0;
	uint8_t   temp3 = 0;
	uint8_t   temp4 = 0;

	uint32_t  size = arrayB.size();

	for ( uint32_t i=0 ; i<size ; i++ )
	{
		ByteAndByte( (*arrayA)[i], arrayB[i], &temp1, &temp2 );
		(*arrayA)[i]    = temp1;

		uint32_t  j = 1;

		do
		{
			ByteAndByte( (*arrayA)[i+j], temp2, &temp3, &temp4 );
			(*arrayA)[i+j] = temp3;

			j++;
		}
		while( temp4>0 );
	}
}

// ArrayA -= ArrayB
/*
static void ArrayMinusEqualArray(std::vector<uint8_t> *arrayA,const std::vector<uint8_t> arrayB)
{
	;
}*/

// ArrayA = ArrayB - ArrayA
/*
static void ArrayMinusEqualArray2(std::vector<uint8_t> *arrayA,const std::vector<uint8_t> arrayB)
{
	;
}*/

void Real::operator +=(const Real &number)
{
	if      ( _this->negative==true  && number._this->negative==true )
	{
		ArrayAndEqualArray(&(_this->data),number._this->data);
	}
	else if ( _this->negative==false && number._this->negative==false )
	{
		ArrayAndEqualArray(&(_this->data),number._this->data);
	}
//	else if ( _this->negative==true  && number._this->negative==false )
//	{
//		if ( isDataBiggerThan(number) )
//		{
//			ArrayMinusEqualArray(&(_this->data),number._this->data);
//		}
//		else if ( isDataSmallerThan(number) )
//		{
//			ArrayMinusEqualArray2(&(_this->data),number._this->data);
//			_this->negative = number._this->negative;
//		}
//		else
//		{
//			_this->data.clear();
//			_this->data.push_back(0);
//		}
//	}
//	else if ( _this->negative==false && number._this->negative==true )
//	{
//		if ( isDataBiggerThan(number) )
//		{
//			ArrayMinusEqualArray(&(_this->data),number._this->data);
//		}
//		else if ( isDataSmallerThan(number) )
//		{
//			ArrayMinusEqualArray2(&(_this->data),number._this->data);
//			_this->negative = number._this->negative;
//		}
//		else
//		{
//			_this->data.clear();
//			_this->data.push_back(0);
//		}
//	}
//	else
//	{
//		toy::Oops(TOY_MARK);
//	}

	CleanZeroEnd(&(_this->data));
}
