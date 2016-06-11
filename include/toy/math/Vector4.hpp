
#pragma once

#include "toy/math/General.hpp"


namespace toy{
namespace math{


template <typename Type>
class Vector4
{
	public:

		union
		{
			struct
			{
				Type    x,y,z,w;
			};
			Type    data[4];
		};

		inline Vector4()
		{
			x=y=z=w=(Type)0;
		}

		inline Vector4(Vector4<Type> &v)
		{
			*this=v;
		}

		inline Vector4(Type xx,Type yy,Type zz,Type ww)
		{
			x=xx;
			y=yy;
			z=zz;
			w=ww;
		}

		~Vector4(){}

		inline void	Set(Type xx,Type yy,Type zz,Type ww)
		{
			x=xx;
			y=yy;
			z=zz;
			w=ww;
		}

		inline Type	Length(void)
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y+z*z+w*w);
			return  result;
		}

		inline void	Normalize(void)
		{
			Type    len;
			len=Length();
			x/=len;
			y/=len;
			z/=len;
			w/=len;
		}

		Vector4<Type> operator =(const Vector4<Type>& v)
		{
			Copy(const_cast<Vector4<Type>&>(v));
			return *this;
		}
		Vector4<Type> operator +=(Vector4<Type>& v)
		{
			x+=v.x;
			y+=v.y;
			z+=v.z;
			w+=v.w;
			return *this;
		}
		Vector4<Type> operator -=(Vector4<Type>& v)
		{
			x-=v.x;
			y-=v.y;
			z-=v.z;
			w-=v.w;
			return *this;
		}

	protected:

		inline void Copy(Vector4<Type>& v)
		{
			x=v.x;
			y=v.y;
			z=v.z;
			w=v.w;
		}
};

}//namespace math
}//namespace toy
