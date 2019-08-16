
#pragma once

#include <cmath>
#include <limits>

namespace toy{
namespace math{

template<typename T1,typename T2, bool T1s, bool T2s>
struct _coreCheckInt{};

template<typename T1,typename T2>
struct _coreCheckInt< T1, T2, true, true >
{
	inline static bool count(const T2 &num)
	{
		if ( std::abs(num) > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			return false;
		}

		return true;
	}
};

template<typename T1,typename T2>
struct _coreCheckInt< T1, T2, true, false >
{
	inline static bool count(const T2 &num)
	{
		if ( num > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			return false;
		}

		return true;
	}
};

template<typename T1,typename T2>
struct _coreCheckInt< T1, T2, false, true >
{
	inline static bool count(const T2 &num)
	{
		if ( num<0 || num > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			return false;
		}

		return true;
	}
};

template<typename T1,typename T2>
struct _coreCheckInt< T1, T2, false, false >
{
	inline static bool count(const T2 &num)
	{
		if ( num > static_cast<T2>(std::numeric_limits<T1>::max()) )
		{
			return false;
		}

		return true;
	}
};

template<typename T1,typename T2>
static inline bool CheckInt(const T2 &num)
{
	static_assert( std::numeric_limits<T1>::is_integer && std::numeric_limits<T2>::is_integer,"must be integer" );

	if ((sizeof(T1)<sizeof(T2)) ||
	    ((sizeof(T1)==sizeof(T2)) &&
	     (std::numeric_limits<T1>::is_signed && ! std::numeric_limits<T2>::is_signed)) )
	{
		return _coreCheckInt<T1,T2,std::numeric_limits<T1>::is_signed,std::numeric_limits<T2>::is_signed>::count(num);
	}

	return true;
}

}}
