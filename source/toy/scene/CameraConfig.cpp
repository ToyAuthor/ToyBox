#include <cstring>
#include "toy/Math.hpp"
#include "toy/scene/CameraConfig.hpp"


using namespace toy;
using namespace scene;


using math::Cot;
using math::Normalize3;
using math::Vector3Dot;
using math::Vector3Cross;
using math::Vector3Invert;
using math::Vector3;

void CameraConfig::ortho(   float w,
                            float h,
                            float near,
                            float far)
{
	memset(_projection.data,0,64);

	_projection.m11 = 2.0f/w;
	_projection.m22 = 2.0f/h;
	_projection.m33 = 2.0f/(near - far);
	_projection.m43 = (far + near)/(near - far);
	_projection.m44 = 1.0f;
}

void CameraConfig::perspect(    float fovy,
                                float aspect,
                                float near,
                                float far)
{
	memset(_projection.data,0,64);

	float      yscale = math::Cot<float>(fovy/2.0f);
	float      xscale = yscale * aspect;

	_projection.m11 = xscale;
	_projection.m22 = yscale;
	_projection.m33 = (far + near)/(near - far);
	_projection.m34 = -1.0f;
	_projection.m43 = 2.0f * far * near / (near - far);
	_projection.m44 = 0.0f;
}

void CameraConfig::lookat(  Vector3<float> eye,
                            Vector3<float> focus,
                            Vector3<float> up)
{
	Vector3<float>	zaxis(eye - focus);zaxis.Normalize();
	Vector3<float>	xaxis(Vector3Cross<float>(Normalize3<float>(up), zaxis));
	Vector3<float>	yaxis(Vector3Cross<float>(zaxis, xaxis));

	memset(_modelview.data,0,64);

	_modelview.SetColumn(1, xaxis);
	_modelview.SetColumn(2, yaxis);
	_modelview.SetColumn(3, zaxis);


	_modelview.m41 = -Vector3Dot<float>(xaxis, eye);
	_modelview.m42 = -Vector3Dot<float>(yaxis, eye);
	_modelview.m43 = -Vector3Dot<float>(zaxis, eye);
	_modelview.m44=1.0f;
}
