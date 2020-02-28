
#pragma once

#include "toy/Math.hpp"

namespace toy{
namespace example{

class TrackballMatirx
{
	public:

		TrackballMatirx()
		{
			toy::math::LookAt(&_modelview,_eye,_focus,_up);
			toy::math::MakePerspect<float>(&_projection,45,_height/_width,1,1000);
		}

		~TrackballMatirx(){}

		void setScreenSize(float width,float height)
		{
			_width  = width;
			_height = height;
			toy::math::MakePerspect<float>(&_projection,45,_height/_width,1,1000);
		}

		auto projection()const ->const toy::math::Matrix4<float>&
		{
			return _projection;
		}

		auto modelview()const ->const toy::math::Matrix4<float>
		{
			return _modelview * (_direct*_directTemp);
		}

		void setMousePosition(int x,int y,bool press)
		{
			_press = press;

			if ( _press )
			{
				_oldPosX = x;
				_oldPosY = y;
			}
			else
			{
				auto  xx = _oldPosX - x;
				auto  yy = _oldPosY - y;

				_directTemp.setEuler(toy::math::Degrees<float>(-yy),toy::math::Degrees<float>(xx),0);
				_direct *= _directTemp;
				_directTemp = toy::math::Quaternion<float>(0,0,0);
			}
		}

		void setMouseMovePosition(int x,int y)
		{
			if ( _press )
			{
				auto  xx = _oldPosX - x;
				auto  yy = _oldPosY - y;

				_directTemp.setEuler(toy::math::Degrees<float>(-yy),toy::math::Degrees<float>(xx),0);
			}
		}

	private:

		toy::math::Matrix4<float>    _projection;
		toy::math::Matrix4<float>    _modelview;

		toy::math::Quaternion<float> _direct     = toy::math::Quaternion<float>(0,0,0);
		toy::math::Quaternion<float> _directTemp = toy::math::Quaternion<float>(0,0,0);

		toy::math::Vector3<float>    _eye   = toy::math::Vector3<float>( 0, 0, 300 );
		toy::math::Vector3<float>    _focus = toy::math::Vector3<float>( 0, 0, 0 );
		toy::math::Vector3<float>    _up    = toy::math::Vector3<float>( 0, 1, 0 );

		float      _width  = 800;
		float      _height = 600;

		int        _oldPosX = 0;
		int        _oldPosY = 0;

		bool       _press = false;
};

}}
