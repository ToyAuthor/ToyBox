
#pragma once

#include <cmath>
#include <cfloat>
#include "toy/Environment.hpp"


namespace toy{
namespace math{

template <typename Type>
Type Min(const Type a,const Type b)
{
	if(a>b)  return b;
	else     return a;
}

template <typename Type>
Type Min(const Type a,const Type b,const Type c)
{
	Type  result;

	if(a>b)  result = b;
	else     result = a;

	if(result>c)  result = c;

	return result;
}

template <typename Type>
Type Min(const Type a,const Type b,const Type c,const Type d)
{
	Type  result;

	if(a>b)  result = b;
	else     result = a;

	if(result>c)  result = c;
	if(result>d)  result = d;

	return result;
}

// Find next power of 2.
// Figure out a number base on 2 and bigger than t and most close t.
template <typename Type>
inline Type Exp1(const Type t)
{
	Type    answer=2;

	while(t>answer)
	{
		answer=answer<<1;
	}

	return answer;
}

// Same function with exp1().
template <typename Type>
inline Type Exp2(const Type t)
{
	Type    answer=2;

	while(t>answer)
	{
		answer*=2;
	}

	return answer;
}

// Figure out a number(f(x)=1+2+4+8+16+...) smaller than t and most close t.
template <typename Type>
inline Type Exp3(const Type t)
{
	Type    answer=1;
	Type    item  =1;

	while(answer<t)
	{
		item=item<<1;
		answer+=item;
	}

	answer-=item;
	return answer;
}

/*
 * cot(x) = cos(x)/sin(x)
 * cot(x) = tan(PI/2 - x)----better  M_PI_2
 */
template <typename Type>
inline Type Cot(const Type t)
{
	return static_cast<Type>(std::tan(1.57079632679489661923 - t));
}

template <typename Type>
inline Type Sqrt(const Type f)
{
	Type    result=(Type)0;

	#if TOY_OPTION_ENABLE_ASSEMBLY
		#if defined(TOY_MSVC)
		__asm
		{
			fld [f]
			fsqrt
			fstp [result]
		}
		#else
			/*__asm__ __volatile__
			(
				"fsqrt\n\t"
				"fstp %0"
				: "=m" (result)
				: "g" (f)
			);*/
			__asm__ __volatile__
			(
				"fld %1\n\t"
				"fsqrt\n\t"
				"fstp %0"
				: "=m" (result)
				: "t" (f)
			);
			/*
			__asm__ __volatile__
			(
				"fsqrt"
				: "+t" (f)
			);
			result=f;*/
		#endif
	#else
		result = std::sqrt(f);
	#endif

	return result;
}

template <typename Type>
inline Type Radians(const Type radians)
{
	return radians;
}

// degrees -> radians
template <typename Type>
inline Type Degrees(const Type degrees)
{
	return degrees * Type(0.01745329251994329576923690768489);
}

// radians -> degrees
template <typename Type>
inline Type RadiansToDegrees(const Type radians)
{
	return radians * Type(57.295779513082320876798154814105);
}

}//namespace math
}//namespace toy
