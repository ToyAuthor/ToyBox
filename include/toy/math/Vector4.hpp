
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

		Vector4():x(Type(0)),y(Type(0)),z(Type(0)),w(Type(0)){}

		Vector4(const Type xx,const Type yy,const Type zz,const Type ww):x(xx),y(yy),z(zz),w(ww){}

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
			return  ::toy::math::Sqrt<Type>(x*x+y*y+z*z+w*w);
		}

		void normalize()
		{
			Type    len = length();
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}

		Vector4<Type> operator +(const Vector4<Type>& v) const
		{
			return Vector4<Type>( x+v.x,
			                      y+v.y,
			                      z+v.z,
			                      w+v.w );
		}

		Vector4<Type> operator -(const Vector4<Type>& v) const
		{
			return Vector4<Type>( x-v.x,
			                      y-v.y,
			                      z-v.z,
			                      w-v.w );
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

		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;
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
