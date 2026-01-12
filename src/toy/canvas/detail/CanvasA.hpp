
#pragma once

#include "toy/canvas/detail/Canvas.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class CanvasA : public toy::canvas::_detail::Canvas
{
	public:

		CanvasA();
		~CanvasA();

		void setImage(float positionX,float positionY,const toy::ImageBuffer &image,toy::canvas::Texture);
		void getImage(float positionX,float positionY,toy::ImageBuffer *image,toy::canvas::Texture);

	private:
};

}}}
