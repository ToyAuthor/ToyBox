
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

		Vector4()
		{
			x=y=z=w=(Type)0;
		}

		Vector4(Type xx,Type yy,Type zz,Type ww)
		{
			x=xx;
			y=yy;
			z=zz;
			w=ww;
		}

		~Vector4(){}

		void set(Type xx,Type yy,Type zz,Type ww)
		{
			x=xx;
			y=yy;
			z=zz;
			w=ww;
		}

		Type length(void)
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y+z*z+w*w);
			return  result;
		}

		void normalize(void)
		{
			Type    len;
			len = length();
			x/=len;
			y/=len;
			z/=len;
			w/=len;
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

	//----------------Maybe not necessary----------------start

		Vector4(const Vector4<Type>& v)
		{
			copy_mykind(const_cast<Vector4<Type>&>(v));
		}

		Vector4<Type> operator =(const Vector4<Type>& v)
		{
			copy_mykind(const_cast<Vector4<Type>&>(v));
			return *this;
		}

	protected:

		inline void copy_mykind(Vector4<Type>& v)
		{
			x=v.x;
			y=v.y;
			z=v.z;
			w=v.w;
		}

	//----------------Maybe not necessary----------------end
};

}//namespace math
}//namespace toy
