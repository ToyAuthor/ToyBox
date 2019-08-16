
#pragma once

#include <cmath>

namespace toy{
namespace math{

inline static float Abs(float num)
{
	return std::fabs(num);
}

inline static void Abs(float *num)
{
	*num = std::fabs(*num);
}

inline static double Abs(double num)
{
	return std::fabs(num);
}

inline static void Abs(double *num)
{
	*num = std::fabs(*num);
}

}}
