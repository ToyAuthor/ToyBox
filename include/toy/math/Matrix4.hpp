
#pragma once

#include "toy/Standard.hpp"
#include "toy/math/Vector3.hpp"
#include "toy/math/Vector4.hpp"
#include "toy/math/Quaternion.hpp"


namespace toy{
namespace math{


// A 4x4 matrix.
template <typename Type>
class Matrix4
{
public:

	struct Matrix
	{
		Type    data[16];
	};

	union
	{
		Type    data[16];

		struct
		{
			Type    m11,m12,m13,m14;
			Type    m21,m22,m23,m24;
			Type    m31,m32,m33,m34;
			Type    m41,m42,m43,m44;
		};

		struct Matrix       matrix;
	};

	Matrix4(){}

	Matrix4(const Quaternion<Type>& q)
	{
		Type   norm = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
		Type   s = (norm > 0) ? 2/norm : 0;

		Type   xx = q.x * q.x * s;
		Type   yy = q.y * q.y * s;
		Type   zz = q.z * q.z * s;
		Type   xy = q.x * q.y * s;
		Type   xz = q.x * q.z * s;
		Type   yz = q.y * q.z * s;
		Type   wx = q.w * q.x * s;
		Type   wy = q.w * q.y * s;
		Type   wz = q.w * q.z * s;

		// x axis
		m11 = Type(1) - (yy + zz);
		m21 = xy + wz;
		m31 = xz - wy;

		// y axis
		m12 = xy - wz;
		m22 = Type(1) - (xx + zz);
		m32 = yz + wx;

		// z axis
		m13 = xz + wy;
		m23 = yz - wx;
		m33 = Type(1) - (xx + yy);

		m41 = m42 = m43 = m14 = m24 = m34 = Type(0);
		m44 = Type(1);
	}

	Matrix4(const Matrix4<Type>& model)
	{
		matrix = model.matrix;
	}

	~Matrix4(){}

	void identity()
	{
		m12=m13=m14=m21=m23=m24=m31=m32=m34=m41=m42=m43=Type(0);
		m11=m22=m33=m44=Type(1);
	}

	void setColumn(const int32_t i,const Vector4<Type> & v)
	{
		#ifdef TOY_OPTION_CHECK
		if(i<1||4<i)toy::Oops(TOY_MARK);
		#endif

		data[i-1]  = v.x;
		data[i+3]  = v.y;
		data[i+7]  = v.z;
		data[i+11] = v.w;
	}

	void setColumn(const int32_t i,const Vector3<Type> & v)
	{
		#ifdef TOY_OPTION_CHECK
		if(i<1||4<i)toy::Oops(TOY_MARK);
		#endif

		data[i-1] = v.x;
		data[i+3] = v.y;
		data[i+7] = v.z;
	}

	Matrix4<Type> operator =(const Matrix4<Type>& model)
	{
		matrix = model.matrix;
		return *this;
	}

	Matrix4<Type> operator *(const Matrix4<Type>& bb) const
	{
		Matrix4<Type>  result;

		result.m11 = m11*bb.m11 + m21*bb.m12 + m31*bb.m13 + m41*bb.m14;
		result.m12 = m12*bb.m11 + m22*bb.m12 + m32*bb.m13 + m42*bb.m14;
		result.m13 = m13*bb.m11 + m23*bb.m12 + m33*bb.m13 + m43*bb.m14;
		result.m14 = m14*bb.m11 + m24*bb.m12 + m34*bb.m13 + m44*bb.m14;

		result.m21 = m11*bb.m21 + m21*bb.m22 + m31*bb.m23 + m41*bb.m24;
		result.m22 = m12*bb.m21 + m22*bb.m22 + m32*bb.m23 + m42*bb.m24;
		result.m23 = m13*bb.m21 + m23*bb.m22 + m33*bb.m23 + m43*bb.m24;
		result.m24 = m14*bb.m21 + m24*bb.m22 + m34*bb.m23 + m44*bb.m24;

		result.m31 = m11*bb.m31 + m21*bb.m32 + m31*bb.m33 + m41*bb.m34;
		result.m32 = m12*bb.m31 + m22*bb.m32 + m32*bb.m33 + m42*bb.m34;
		result.m33 = m13*bb.m31 + m23*bb.m32 + m33*bb.m33 + m43*bb.m34;
		result.m34 = m14*bb.m31 + m24*bb.m32 + m34*bb.m33 + m44*bb.m34;

		result.m41 = m11*bb.m41 + m21*bb.m42 + m31*bb.m43 + m41*bb.m44;
		result.m42 = m12*bb.m41 + m22*bb.m42 + m32*bb.m43 + m42*bb.m44;
		result.m43 = m13*bb.m41 + m23*bb.m42 + m33*bb.m43 + m43*bb.m44;
		result.m44 = m14*bb.m41 + m24*bb.m42 + m34*bb.m43 + m44*bb.m44;

		return result;
	}

	void operator *=(const Matrix4<Type>& model)
	{
		Matrix4<Type>  result = (*this)*model;
		*this = result;
	}

	// translation
	void operator +=(const toy::math::Vector3<Type>& place)
	{
		m41 = m11*place.x + m21*place.y + m31*place.z + m41;
		m42 = m12*place.x + m22*place.y + m32*place.z + m42;
		m43 = m13*place.x + m23*place.y + m33*place.z + m43;
		m44 = m14*place.x + m24*place.y + m34*place.z + m44;
	}
};


}//namespace math
}//namespace toy
