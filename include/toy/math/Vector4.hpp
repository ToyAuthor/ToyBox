
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
			x = y = z = w = (Type)0;
		}

		Vector4(const Type xx,const Type yy,const Type zz,const Type ww)
		{
			x = xx;
			y = yy;
			z = zz;
			w = ww;
		}

		~Vector4(){}

		void set(const Type xx,const Type yy,const Type zz,const Type ww)
		{
			x = xx;
			y = yy;
			z = zz;
			w = ww;
		}

		Type length() const
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y+z*z+w*w);
			return  result;
		}

		void normalize()
		{
			Type    len;
			len = length();
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}

		Vector4<Type> operator +(const Vector4<Type>& v) const
		{
			Vector4<Type>   result;
			result.x = x+v.x;
			result.y = y+v.y;
			result.z = z+v.z;
			result.w = z+v.w;
			return result;
		}

		Vector4<Type> operator -(const Vector4<Type>& v) const
		{
			Vector4<Type>   result;
			result.x = x-v.x;
			result.y = y-v.y;
			result.z = z-v.z;
			result.w = z-v.w;
			return result;
		}

		Vector4<Type> operator +=(const Vector4<Type>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}

		Vector4<Type> operator -=(const Vector4<Type>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		Vector4(const Vector4<Type>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}

		Vector4<Type> operator =(const Vector4<Type>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
			return *this;
		}
};

}//namespace math
}//namespace toy
