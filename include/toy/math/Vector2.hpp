
#pragma once


#include "toy/math/General.hpp"


namespace toy{
namespace math{



template <typename Type>
class Vector2
{
	public:

		union
		{
			struct
			{
				Type    x;
				Type    y;
			};
			Type    data[2];
		};

		Vector2()
		{
			x=y=(Type)0;
		}

		Vector2(const Type _x,const Type _y)
		{
			x=_x;
			y=_y;
		}

		~Vector2(){}

		void set(const Type _x,const Type _y)
		{
			x=_x;
			y=_y;
		}

		Type length() const
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y);
			return  result;
		}

		void normalize()
		{
			Type    len;
			len = length();
			x/=len;
			y/=len;
		}

		Vector2<Type> operator +(const Vector2<Type>& v) const
		{
			Vector2<Type>   result;
			result.x = x+v.x;
			result.y = y+v.y;
			return result;
		}

		Vector2<Type> operator -(const Vector2<Type>& v) const
		{
			Vector2<Type>   result;
			result.x = x-v.x;
			result.y = y-v.y;
			return result;
		}

		Vector2<Type> operator +=(const Vector2<Type>& v)
		{
			x+=v.x;
			y+=v.y;
			return *this;
		}

		Vector2<Type> operator -=(const Vector2<Type>& v)
		{
			x-=v.x;
			y-=v.y;
			return *this;
		}

		Vector2(const Vector2<Type> &v)
		{
			x = v.x;
			y = v.y;
		}

		Vector2<Type> operator =(const Vector2<Type>& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}
};




}//namespace math
}//namespace toy
