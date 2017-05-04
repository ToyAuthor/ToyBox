
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

		Vector2(Type _x,Type _y)
		{
			x=_x;
			y=_y;
		}

		~Vector2(){}

		void set(Type _x,Type _y)
		{
			x=_x;
			y=_y;
		}

		Type length(void)
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y);
			return  result;
		}

		void normalize(void)
		{
			Type    len;
			len = length();
			x/=len;
			y/=len;
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

	//----------------Maybe not necessary----------------start

		Vector2(const Vector2<Type> &v)
		{
			copy_mykind(const_cast<Vector2<Type>&>(v));
		}

		Vector2<Type> operator =(const Vector2<Type>& v)
		{
			copy_mykind(const_cast<Vector2<Type>&>(v));
			return *this;
		}

	protected:

		inline void copy_mykind(Vector2<Type>& v)
		{
			x=v.x;
			y=v.y;
		}

	//----------------Maybe not necessary----------------end
};




}//namespace math
}//namespace toy
