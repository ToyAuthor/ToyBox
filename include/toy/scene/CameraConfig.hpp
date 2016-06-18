
#pragma once

#include "toy/Standard.hpp"
#include "toy/math/Vector3.hpp"
#include "toy/math/Matrix4.hpp"

namespace toy{
namespace scene{


class TOY_API CameraConfig
{
	public:

		CameraConfig(){}
		CameraConfig(const CameraConfig& model)
		{
			_projection=model._projection;
			_modelview =model._modelview;
		}

		~CameraConfig(){}

		void    ortho(float w, float h, float near, float far);
		void    perspect(float fovy, float aspect, float near, float far);

		inline math::Matrix4<float> projection(){return _projection;}
		inline math::Matrix4<float> modelview(){return _modelview;}
		inline void projection(math::Matrix4<float> m){_projection=std::move(m);}
		inline void modelview(math::Matrix4<float> m){_modelview=std::move(m);}


		void    lookat( math::Vector3<float> eye,       // Location of camera.
		                math::Vector3<float> focus,     // Camera look at where.
		                math::Vector3<float> up         // The direction of top of camera. Usually use (0,1,0).
		                );

		CameraConfig& operator =(const CameraConfig& model)
		{
			_projection=model._projection;
			_modelview =model._modelview;
			return *this;
		}

	private:

		math::Matrix4<float>     _projection;
		math::Matrix4<float>     _modelview;
};

}}
