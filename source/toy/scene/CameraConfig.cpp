#include <cstring>
#include "toy/Math.hpp"
#include "toy/scene/CameraConfig.hpp"

using namespace toy;
using namespace scene;

void CameraConfig::ortho( const float width,
                          const float height,
                          const float near,
                          const float far )
{
	toy::math::MakeOrtho(&_projection,width,height,near,far);
}

void CameraConfig::perspect( const float fovy,
                             const float aspect,
                             const float near,
                             const float far )
{
	toy::math::MakePerspect(&_projection,fovy,aspect,near,far);
}

void CameraConfig::lookat( const toy::math::Vector3<float> &eye,
                           const toy::math::Vector3<float> &focus,
                           const toy::math::Vector3<float> &up )
{
	toy::math::LookAt(&_modelview,eye,focus,up);
}

auto CameraConfig::projection() const->const math::Matrix4<float>&
{
	return _projection;
}

auto CameraConfig::modelview() const->const math::Matrix4<float>&
{
	return _modelview;
}

void CameraConfig::projection(const math::Matrix4<float> &m)
{
	_projection = m;
}

void CameraConfig::modelview(const math::Matrix4<float> &m)
{
	_modelview = m;
}
