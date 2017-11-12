
#pragma once

#include "toy/Standard.hpp"
#include "toy/scene/Export.hpp"
#include "toy/math/Vector3.hpp"
#include "toy/math/Matrix4.hpp"

namespace toy{
namespace scene{

class TOY_API_SCENE CameraConfig
{
	public:

		CameraConfig(){}
		~CameraConfig(){}

		void ortho(const float w, const float h, const float near, const float far);

		void perspect( const float fovy,     // Radians
		               const float aspect,   // height/width
		               const float near,
		               const float far );

		auto projection()const ->const toy::math::Matrix4<float>&;
		void projection(         const toy::math::Matrix4<float>&);
		auto modelview()const  ->const toy::math::Matrix4<float>&;
		void modelview(          const toy::math::Matrix4<float>&);

		void lookat( const toy::math::Vector3<float> &eye,       // Location of camera.
		             const toy::math::Vector3<float> &focus,     // Camera look at where.
		             const toy::math::Vector3<float> &up );      // The direction of the top of camera. Usually use (0,1,0).

	private:

		toy::math::Matrix4<float>     _projection;
		toy::math::Matrix4<float>     _modelview;
};

}}
