
#pragma once

#include "toy/math/General.hpp"


namespace toy{
namespace math{


template <typename Type>
class Vector3
{
	public:

		union
		{
			struct
			{
				Type    x,y,z;
			};
			Type    data[3];
		};

		Vector3(){}

		Vector3(const Type xx,const Type yy,const Type zz)
		{
			x = xx;
			y = yy;
			z = zz;
		}

		~Vector3(){}

		void set(const Type xx,const Type yy,const Type zz)
		{
			x = xx;
			y = yy;
			z = zz;
		}

		Type length() const
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y+z*z);
			return  result;
		}

		void normalize()
		{
			Type    len = length();

			x /= len;
			y /= len;
			z /= len;
		}

		Vector3<Type> operator +(const Vector3<Type>& v) const
		{
			Vector3<Type>   result;
			result.x = x+v.x;
			result.y = y+v.y;
			result.z = z+v.z;
			return result;
		}

		Vector3<Type> operator -(const Vector3<Type>& v) const
		{
			Vector3<Type>   result;
			result.x = x-v.x;
			result.y = y-v.y;
			result.z = z-v.z;
			return result;
		}

		Vector3<Type> operator +=(const Vector3<Type>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vector3<Type> operator -=(const Vector3<Type>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		void invert(void)
		{
			x =- x;
			y =- y;
			z =- z;
		}

		Vector3(const Vector3<Type> &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		Vector3<Type> operator =(const Vector3<Type> &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}
};


}//namespace math
}//namespace toy
