
#pragma once

#include <cstdint>
#include <string>
#include "toy/math/Export.hpp"

namespace toy{
namespace math{

struct IntPrivate;

class TOY_API_MATH Int
{
	public:

		~Int();
		Int(const Int &number);
		Int(int8_t   number);
		Int(uint8_t  number);
		Int(int16_t  number);
		Int(uint16_t number);
		Int(int32_t  number);
		Int(uint32_t number);
		Int(int64_t  number);
		Int(uint64_t number);
		Int(const  int8_t *number, int datasize, bool negative=false);
		Int(const uint8_t *number, int datasize, bool negative=false);

		bool get( int8_t  *number) const;
		bool get(uint8_t  *number) const;
		bool get( int16_t *number) const;
		bool get(uint16_t *number) const;
		bool get( int32_t *number) const;
		bool get(uint32_t *number) const;
		bool get( int64_t *number) const;
		bool get(uint64_t *number) const;
		bool get(std::string *number) const;

	//	bool setRawData(const uint8_t *number,int dataSize);
	//	int  getRawData(      uint8_t *number);    // getRawData(nullptr) return raw data size.

	//	Int(float number);

	//	auto operator / (const Int &number) const -> const Int &number;
	//	void operator /=(const Int &number);

	//	auto operator * (const Int &number) const -> const Int &number;
	//	void operator *=(const Int &number);

	//	auto operator + (const Int &number) const -> const Int &number;
		void operator +=(const Int &number);

	//	auto operator - (const Int &number) const -> const Int &number;
	//	void operator -=(const Int &number);

	//	void operator >>(int);
	//	void operator <<(int);

	//	bool isAbsoluteValueBiggerThan (const Int &number);
	//	bool isAbsoluteValueSmallerThan(const Int &number);

	//	bool operator > (const Int &number);
	//	bool operator < (const Int &number);
	//	bool operator <=(const Int &number);
	//	bool operator >=(const Int &number);
	//	bool operator ==(const Int &number);

	private:

		IntPrivate* _this = nullptr;
};

}}
