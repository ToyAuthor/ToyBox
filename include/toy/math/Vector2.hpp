
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

		inline Vector2()
		{
			x=y=(Type)0;
		}

		inline Vector2(const Vector2<Type> &v)
		{
			Copy(const_cast<Vector2<Type>&>(v));
		}

		inline Vector2(Type _x,Type _y)
		{
			x=_x;
			y=_y;
		}

		~Vector2(){}

		inline void	Set(Type _x,Type _y)
		{
			x=_x;
			y=_y;
		}

		inline Type	Length(void)
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y);
			return  result;
		}

		inline void	Normalize(void)
		{
			Type    len;
			len=Length();
			x/=len;
			y/=len;
		}

		Vector2<Type> operator =(const Vector2<Type>& v)
		{
			Copy(const_cast<Vector2<Type>&>(v));
			return *this;
		}

		Vector2<Type> operator +=(Vector2<Type>& v)
		{
			x+=v.x;
			y+=v.y;
			return *this;
		}

		Vector2<Type> operator -=(Vector2<Type>& v)
		{
			x-=v.x;
			y-=v.y;
			return *this;
		}

	protected:

		inline void Copy(Vector2<Type>& v)
		{
			x=v.x;
			y=v.y;
		}
};




}//namespace math
}//namespace toy
