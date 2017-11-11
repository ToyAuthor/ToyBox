
#pragma once

#include "toy/math/General.hpp"


namespace toy{
namespace math{


template <typename Type>
class Quaternion
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

		// Axis angles
		Quaternion(const Type ax,const Type ay,const Type az,const Type angle)
		{
			auto sinang = std::sin(angle / Type(2));

			x = ax * sinang;
			y = ay * sinang;
			z = az * sinang;
			w = std::cos(angle / Type(2));
		}

		// Euler angles
		Quaternion(const Type ax,const Type ay,const Type az)
		{
			x = std::sin(ay/Type(2))*std::sin(az/Type(2))*std::cos(ax/Type(2)) + std::cos(ay/Type(2))*std::cos(az/Type(2))*std::sin(ax/Type(2));
			y = std::sin(ay/Type(2))*std::cos(az/Type(2))*std::cos(ax/Type(2)) + std::cos(ay/Type(2))*std::sin(az/Type(2))*std::sin(ax/Type(2));
			z = std::cos(ay/Type(2))*std::sin(az/Type(2))*std::cos(ax/Type(2)) - std::sin(ay/Type(2))*std::cos(az/Type(2))*std::sin(ax/Type(2));
			w = std::cos(ay/Type(2))*std::cos(az/Type(2))*std::cos(ax/Type(2)) - std::sin(ay/Type(2))*std::sin(az/Type(2))*std::sin(ax/Type(2));
		}

		~Quaternion(){}

		void set(const Type xx,const Type yy,const Type zz,const Type ww)
		{
			x = xx;
			y = yy;
			z = zz;
			w = ww;
		}

		auto axis() const ->const toy::math::Vector3<Type>
		{
		//	auto  angle = Type(2) * std::acos(w);

			auto  scale  = toy::math::Sqrt<Type>(x*x+y*y+z*z);

			toy::math::Vector3<Type>   result( x/scale, y/scale, z/scale );
			//result.normalize();

			return result;
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

		Quaternion<Type> operator +(const Quaternion<Type>& v) const
		{
			Quaternion<Type>   result;
			result.x = x+v.x;
			result.y = y+v.y;
			result.z = z+v.z;
			result.w = z+v.w;
			return result;
		}

		Quaternion<Type> operator -(const Quaternion<Type>& v) const
		{
			Quaternion<Type>   result;
			result.x = x-v.x;
			result.y = y-v.y;
			result.z = z-v.z;
			result.w = z-v.w;
			return result;
		}

		Quaternion<Type> operator +=(const Quaternion<Type>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}

		Quaternion<Type> operator -=(const Quaternion<Type>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		const Quaternion<Type>& operator *(const Quaternion<Type> &v) const
		{
			static Quaternion<Type> ret;

			ret.x = y*v.z - z*v.y + w*v.x + x*v.w;
			ret.y = z*v.x - x*v.z + w*v.y + y*v.w;
			ret.z = x*v.y - y*v.x + w*v.z + z*v.w;
			ret.w = w*v.w - x*v.x - y*v.y - z*v.z;

			return ret;
		}

		void operator *=(const Quaternion<Type> &v)
		{
			Quaternion<Type> ret = (*this)*v;
			*this = ret;
		}

		Quaternion(const Quaternion<Type>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}

		Quaternion<Type> operator =(const Quaternion<Type>& v)
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
