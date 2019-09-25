
#pragma once

#include <cstdlib>     // Include it but <cmath>, because std::abs has ambiguous issue at <cmath>.
#include <limits>
#include <toy/Exception.hpp>

namespace toy{
namespace math{

template<typename T1,typename T2, bool T1s, bool T2s>
struct _coreSafeInt{};

template<typename T1,typename T2>
struct _coreSafeInt< T1, T2, true, true >
{
	inline static void count(const T2 &num,const char *file,int line)
	{
		if ( std::abs(num) > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			throw std::runtime_error(toy::MarkString(file,line));
		}
	}
};

template<typename T1,typename T2>
struct _coreSafeInt< T1, T2, true, false >
{
	inline static void count(const T2 &num,const char *file,int line)
	{
		if ( num > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			throw std::runtime_error(toy::MarkString(file,line));
		}
	}
};

template<typename T1,typename T2>
struct _coreSafeInt< T1, T2, false, true >
{
	inline static void count(const T2 &num,const char *file,int line)
	{
		if ( num<0 || num > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			throw std::runtime_error(toy::MarkString(file,line));
		}
	}
};

template<typename T1,typename T2>
struct _coreSafeInt< T1, T2, false, false >
{
	inline static void count(const T2 &num,const char *file,int line)
	{
		if ( num > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			throw std::runtime_error(toy::MarkString(file,line));
		}
	}
};

template<typename T1,typename T2>
static inline void SafeInt(T1 *num1,const T2 &num2,const char *file,int line)
{
	static_assert( std::numeric_limits<T1>::is_integer && std::numeric_limits<T2>::is_integer,"must be integer" );

	if ((sizeof(T1)<sizeof(T2)) ||
	    ((sizeof(T1)==sizeof(T2)) &&
	     (std::numeric_limits<T1>::is_signed && ! std::numeric_limits<T2>::is_signed)) )
	{
		_coreSafeInt<T1,T2,std::numeric_limits<T1>::is_signed,std::numeric_limits<T2>::is_signed>::count(num2,file,line);
	}

	*num1 = static_cast<T1>(num2);
}

template<typename T1,typename T2>
static inline T1 SafeInt(const T2 &num,const char *file,int line)
{
	static_assert( std::numeric_limits<T1>::is_integer && std::numeric_limits<T2>::is_integer,"must be integer" );

	if ((sizeof(T1)<sizeof(T2)) ||
	    ((sizeof(T1)==sizeof(T2)) &&
	     (std::numeric_limits<T1>::is_signed && ! std::numeric_limits<T2>::is_signed)) )
	{
		_coreSafeInt<T1,T2,std::numeric_limits<T1>::is_signed,std::numeric_limits<T2>::is_signed>::count(num,file,line);
	}

	return static_cast<T1>(num);
}

}}
