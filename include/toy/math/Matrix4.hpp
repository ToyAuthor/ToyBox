
#pragma once

#include "toy/Standard.hpp"
#include "toy/math/Vector4.hpp"


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

		struct Matrix       mMatrix;
	};

	Matrix4(){}

	Matrix4(const Matrix4<Type>& model)
	{
		mMatrix=model.mMatrix;
	}

	~Matrix4(){}

	void	Identity(void)
	{
		m12=m13=m14=m21=m23=m24=m31=m32=m34=m41=m42=m43=(Type)0;
		m11=m22=m33=m44=(Type)1;
	}

	void	SetColumn(int32_t i,Vector4<Type> & v)
	{
		#ifdef TOY_OPTION_CHECK
		if(i<1||4<i)toy::Oops(TOY_MARK);
		#endif

		data[i-1]=v.x;
		data[i+3]=v.y;
		data[i+7]=v.z;
		data[i+11]=v.w;
	}

	void	SetColumn(int32_t i,Vector3<Type> & v)
	{
		#ifdef TOY_OPTION_CHECK
		if(i<1||4<i)toy::Oops(TOY_MARK);
		#endif

		data[i-1]=v.x;
		data[i+3]=v.y;
		data[i+7]=v.z;
	}

	Matrix4<Type>& operator =(const Matrix4<Type>& model)
	{
		mMatrix=model.mMatrix;
		return *this;
	}

//protected:

};


}//namespace math
}//namespace toy
