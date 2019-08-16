
#pragma once

#include <cstdint>

namespace toy{
namespace math{

inline static int8_t Abs(int8_t num)
{
	uint8_t temp = num >> 7;
	num ^= temp;
	num += temp & 1;

	return num;
}

inline static void Abs(int8_t *num)
{
	uint8_t temp = *num >> 7;
	*num ^= temp;
	*num += temp & 1;
}

inline static int16_t Abs(int16_t num)
{
	uint16_t temp = num >> 15;
	num ^= temp;
	num += temp & 1;

	return num;
}

inline static void Abs(int16_t *num)
{
	uint16_t temp = *num >> 15;
	*num ^= temp;
	*num += temp & 1;
}

inline static int32_t Abs(int32_t num)
{
	uint32_t temp = num >> 31;
	num ^= temp;
	num += temp & 1;

	return num;
}

inline static void Abs(int32_t *num)
{
	uint32_t temp = *num >> 31;
	*num ^= temp;
	*num += temp & 1;
}

inline static int64_t Abs(int64_t num)
{
	uint64_t temp = num >> 63;
	num ^= temp;
	num += temp & 1;

	return num;
}

inline static void Abs(int64_t *num)
{
	uint64_t temp = *num >> 63;
	*num ^= temp;
	*num += temp & 1;
}

}}
