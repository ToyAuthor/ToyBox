
#pragma once


#include "toy/math/General.hpp"
#include "toy/math/Vector2.hpp"
#include "toy/math/Vector3.hpp"
#include "toy/math/Vector4.hpp"


namespace toy{
namespace math{

//-----------------3 dimension------------------start


template <typename Type>
inline Vector3<Type> CreateV3(Type x,Type y,Type z)
{
	return Vector3<Type>(x,y,z);
}

template <typename Type>
inline Vector3<Type> Normalize3(Vector3<Type> t)
{
	Vector3<Type>    result;

	result=t;
	result.Normalize();

	return result;
}

// "->" become "<-"
template <typename Type>
inline Vector3<Type> Vector3Invert(Vector3<Type> t)
{
	Vector3<Type>    result;

	result=t;
	result.Invert();

	return result;
}

template <typename Type>
inline Type Vector3Dot(Vector3<Type> a,Vector3<Type> b)
{
	return  a.x*b.x+a.y*b.y+a.z*b.z;
}

template <typename Type>
inline Vector3<Type> Vector3Cross(Vector3<Type> a,Vector3<Type> b)
{
	Vector3<Type>    result;

	result.Set( a.y*b.z-a.z*b.y,
	            a.z*b.x-a.x*b.z,
	            a.x*b.y-a.y*b.x );

	return result;
}

/*
template <typename Type>
inline Vector3<Type> Vector3Cross(Vector4<Type> &a,Vector4<Type> &b)
{
	Vector3<Type>   result;
	return result;
}*/

//-----------------3 dimension------------------end



}//namespace math
}//namespace toy
