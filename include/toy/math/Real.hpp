
#pragma once

#include <cstdint>
#include "toy/math/Export.hpp"

namespace toy{
namespace math{

struct RealPrivate;

class TOY_API_MATH Real
{
	public:

		~Real();
		Real(const Real &number);
		Real(int8_t   number);
		Real(uint8_t  number);
		Real(int16_t  number);
		Real(uint16_t number);
		Real(int32_t  number);
		Real(uint32_t number);
		Real(int64_t  number);
		Real(uint64_t number);
		Real(const  int8_t *number, int datasize,bool negative=false);
		Real(const uint8_t *number, int datasize,bool negative=false);

		bool get( int8_t  *number) const;
		bool get(uint8_t  *number) const;
		bool get( int16_t *number) const;
		bool get(uint16_t *number) const;
		bool get( int32_t *number) const;
		bool get(uint32_t *number) const;
		bool get( int64_t *number) const;
		bool get(uint64_t *number) const;

	//	bool setRawData(const uint8_t *number,int dataSize);
	//	int  getRawData(      uint8_t *number);    // getRawData(nullptr) return raw data size.

	//	Real(float number);

	//	auto operator / (const Real &number) const -> const Real &number;
	//	void operator /=(const Real &number);

	//	auto operator * (const Real &number) const -> const Real &number;
	//	void operator *=(const Real &number);

	//	auto operator + (const Real &number) const -> const Real &number;
	//	void operator +=(const Real &number);

	//	auto operator - (const Real &number) const -> const Real &number;
	//	void operator -=(const Real &number);

	private:

		RealPrivate* _this = nullptr;
};

}}
