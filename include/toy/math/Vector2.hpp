
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

		Vector2():x(Type(0)),y(Type(0)){}

		Vector2(const Type xx,const Type yy):x(xx),y(yy){}

		~Vector2(){}

		void set(const Type xx,const Type yy)
		{
			x = xx;
			y = yy;
		}

		Type length() const
		{
			return ::toy::math::Sqrt<Type>(x*x+y*y);
		}

		void normalize()
		{
			Type    len = length();
			x /= len;
			y /= len;
		}

		Vector2<Type> operator +(const Vector2<Type>& v) const
		{
			return Vector2<Type>( x+v.x,
			                      y+v.y );
		}

		Vector2<Type> operator -(const Vector2<Type>& v) const
		{
			return Vector2<Type>( x-v.x,
			                      y-v.y );
		}

		Vector2<Type> operator +=(const Vector2<Type>& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2<Type> operator -=(const Vector2<Type>& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		void invert()
		{
			x = -x;
			y = -y;
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
