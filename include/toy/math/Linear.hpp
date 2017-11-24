
#pragma once

#include <cstring>
#include "toy/math/General.hpp"
#include "toy/math/Vector2.hpp"
#include "toy/math/Vector3.hpp"
#include "toy/math/Vector4.hpp"
#include "toy/math/Matrix4.hpp"


namespace toy{
namespace math{

//-----------------3 dimension------------------start


template <typename Type>
inline auto CreateV3(const Type x,const Type y,const Type z)->::toy::math::Vector3<Type>
{
	return ::toy::math::Vector3<Type>(x,y,z);
}

template <typename Type>
inline auto Normalize3(const ::toy::math::Vector3<Type> &t)->::toy::math::Vector3<Type>
{
	::toy::math::Vector3<Type>    result = t;
	result.normalize();

	return result;
}

template <typename Type>
inline auto Vector3Invert(const ::toy::math::Vector3<Type> &t)->::toy::math::Vector3<Type>
{
	::toy::math::Vector3<Type>    result = t;
	result.invert();

	return result;
}

template <typename Type>
inline Type Vector3Dot(const ::toy::math::Vector3<Type> &a,
                       const ::toy::math::Vector3<Type> &b)
{
	return  a.x*b.x+a.y*b.y+a.z*b.z;
}

template <typename Type>
inline auto Vector3Cross( const ::toy::math::Vector3<Type> a,
                          const ::toy::math::Vector3<Type> b )->::toy::math::Vector3<Type>
{
	return ::toy::math::Vector3<Type>( a.y*b.z-a.z*b.y,
	                                   a.z*b.x-a.x*b.z,
	                                   a.x*b.y-a.y*b.x );
}


//-----------------3 dimension------------------end

template <typename Type>
inline void MakeOrtho( ::toy::math::Matrix4<Type> *mat,
                       const Type &w,      // width
                       const Type &h,      // height
                       const Type &n,      // near
                       const Type &f )     // far
{
	std::memset(mat->data,0,16*sizeof(Type));

	mat->m11 = Type(2)/w;
	mat->m22 = Type(2)/h;
	mat->m33 = Type(2)/(n - f);
	mat->m43 = (f + n)/(n - f);
	mat->m44 = Type(1);
}

template <typename Type>
inline auto MakeOrtho( const Type &w,      // width
                       const Type &h,      // height
                       const Type &n,      // near
                       const Type &f       // far
                       )->::toy::math::Matrix4<Type>
{
	::toy::math::Matrix4<Type>  mat;

	::toy::math::MakeOrtho(&mat,w,h,n,f);

	return mat;
}

template <typename Type>
inline void MakePerspect( ::toy::math::Matrix4<Type> *mat,
                          const Type &v,    // fovy
                          const Type &a,    // aspect
                          const Type &n,    // near
                          const Type &f )   // far
{
	std::memset(mat->data,0,16*sizeof(Type));

	Type      yscale =  ::toy::math::Cot<Type>(v/Type(2));
	Type      xscale = yscale * a;

	mat->m11 = xscale;
	mat->m22 = yscale;
	mat->m33 = (f + n)/(n - f);
	mat->m34 = -Type(1);
	mat->m43 = Type(2) * f * n / (n - f);
	mat->m44 = Type(0);
}

template <typename Type>
inline auto MakePerspect( const Type &v,    // fovy
                          const Type &a,    // aspect
                          const Type &n,    // near
                          const Type &f     // far
                          )->::toy::math::Matrix4<Type>
{
	::toy::math::Matrix4<Type>  mat;

	::toy::math::MakePerspect(&mat,v,a,n,f);

	return mat;
}

template <typename Type>
inline void LookAt( ::toy::math::Matrix4<Type> *mat,
                    const ::toy::math::Vector3<Type> &eye,
                    const ::toy::math::Vector3<Type> &focus,
                    const ::toy::math::Vector3<Type> &up)
{
	namespace temp = ::toy::math;

	temp::Vector3<Type>	zaxis(eye - focus);zaxis.normalize();
	temp::Vector3<Type>	xaxis(temp::Vector3Cross<Type>(temp::Normalize3<Type>(up), zaxis));
	temp::Vector3<Type>	yaxis(temp::Vector3Cross<Type>(zaxis, xaxis));

	std::memset(mat->data,0,16*sizeof(Type));

	mat->setColumn(Type(1), xaxis);
	mat->setColumn(Type(2), yaxis);
	mat->setColumn(Type(3), zaxis);

	mat->m41 = -temp::Vector3Dot<Type>(xaxis, eye);
	mat->m42 = -temp::Vector3Dot<Type>(yaxis, eye);
	mat->m43 = -temp::Vector3Dot<Type>(zaxis, eye);
	mat->m44 = Type(1);
}

template <typename Type>
inline auto LookAt( const ::toy::math::Vector3<Type> &eye,
                    const ::toy::math::Vector3<Type> &focus,
                    const ::toy::math::Vector3<Type> &up
                    )->::toy::math::Matrix4<Type>
{
	::toy::math::Matrix4<Type>  mat;

	::toy::math::LookAt(&mat,eye,focus,up);

	return mat;
}

}//namespace math
}//namespace toy
