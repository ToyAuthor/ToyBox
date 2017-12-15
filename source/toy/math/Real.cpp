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

	int16_t  temp = number%256;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - _this->data[0])>>8);
}

Real::Real(uint16_t number):_this(new struct RealPrivate)
{
	uint16_t  temp = number%256;
	_this->data.push_back( temp);  if ( temp==number ) return;
	_this->data.push_back((number - _this->data[0])>>8);
}

Real::Real(int32_t number):_this(new struct RealPrivate)
{
	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	int32_t  temp = number%256;
	_this->data.push_back( temp);                          if ( temp==number ) return; temp = number%65536;
	_this->data.push_back((temp   - _this->data[0] )>>8 ); if ( temp==number ) return; temp = number%16777216;
	_this->data.push_back((temp   - number%65536   )>>16); if ( temp==number ) return;
	_this->data.push_back((number - number%16777216)>>24);
}

Real::Real(uint32_t number):_this(new struct RealPrivate)
{
	uint32_t  temp = number%256;
	_this->data.push_back( temp);                          if ( temp==number ) return; temp = number%65536;
	_this->data.push_back((temp   - _this->data[0] )>>8 ); if ( temp==number ) return; temp = number%16777216;
	_this->data.push_back((temp   - number%65536   )>>16); if ( temp==number ) return;
	_this->data.push_back((number - number%16777216)>>24);
}

Real::Real(int64_t number):_this(new struct RealPrivate)
{
	if ( number<0 )
	{
		_this->negative = true;
		number *= -1;
	}

	int64_t  temp = number%256;
	_this->data.push_back( temp);                                   if ( temp==number ) return; temp = number%65536;
	_this->data.push_back((temp   - _this->data[0])          >>8 ); if ( temp==number ) return; temp = number%16777216;
	_this->data.push_back((temp   - number%65536)            >>16); if ( temp==number ) return; temp = number%4294967296;
	_this->data.push_back((temp   - number%16777216)         >>24); if ( temp==number ) return; temp = number%1099511627776;
	_this->data.push_back((temp   - number%4294967296)       >>32); if ( temp==number ) return; temp = number%281474976710656;
	_this->data.push_back((temp   - number%1099511627776)    >>40); if ( temp==number ) return; temp = number%72057594037927936;
	_this->data.push_back((temp   - number%281474976710656)  >>48); if ( temp==number ) return;
	_this->data.push_back((number - number%72057594037927936)>>56);
}

Real::Real(uint64_t number):_this(new struct RealPrivate)
{
	uint64_t  temp = number%256;
	_this->data.push_back( temp);                                   if ( temp==number ) return; temp = number%65536;
	_this->data.push_back((temp   - _this->data[0])          >>8 ); if ( temp==number ) return; temp = number%16777216;
	_this->data.push_back((temp   - number%65536)            >>16); if ( temp==number ) return; temp = number%4294967296;
	_this->data.push_back((temp   - number%16777216)         >>24); if ( temp==number ) return; temp = number%1099511627776;
	_this->data.push_back((temp   - number%4294967296)       >>32); if ( temp==number ) return; temp = number%281474976710656;
	_this->data.push_back((temp   - number%1099511627776)    >>40); if ( temp==number ) return; temp = number%72057594037927936;
	_this->data.push_back((temp   - number%281474976710656)  >>48); if ( temp==number ) return;
	_this->data.push_back((number - number%72057594037927936)>>56);
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
