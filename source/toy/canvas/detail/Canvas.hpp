
#pragma once

#include "toy/Standard.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/canvas/Texture.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class Canvas
{
	public:

		Canvas(){}
		virtual ~Canvas(){}

		virtual void setImage(float positionX,float positionY,const toy::ImageBuffer &image,toy::canvas::Texture)=0;
		virtual void getImage(float positionX,float positionY,toy::ImageBuffer *image,toy::canvas::Texture)=0;

};

}}}
