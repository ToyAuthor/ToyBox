
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

		Vector3(Type xx,Type yy,Type zz)
		{
			x=xx;
			y=yy;
			z=zz;
		}

		~Vector3(){}

		void set(Type xx,Type yy,Type zz)
		{
			x=xx;
			y=yy;
			z=zz;
		}

		Type length(void)
		{
			Type    result;
			result = math::Sqrt<Type>(x*x+y*y+z*z);
			return  result;
		}

		void normalize(void)
		{
			Type    len = length();
			x/=len;
			y/=len;
			z/=len;
		}

		Vector3<Type>& operator -(Vector3<Type>& v)
		{
			static  Vector3<Type>   result;
			result.x=x-v.x;
			result.y=y-v.y;
			result.z=z-v.z;
			return  result;
		}

		void invert(void)
		{
			x=-x;
			y=-y;
			z=-z;
		}

	//----------------Maybe not necessary----------------start

		Vector3(const Vector3<Type> &v)
		{
			copy_mykind(v);
		}

		Vector3<Type> operator =(const Vector3<Type> &v)
		{
			copy_mykind(v);
			return *this;
		}

	protected:

		void copy_mykind(const Vector3<Type> &v)
		{
			x=v.x;
			y=v.y;
			z=v.z;
		}

	//----------------Maybe not necessary----------------end
};


}//namespace math
}//namespace toy
