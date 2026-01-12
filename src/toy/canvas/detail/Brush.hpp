
#pragma once

#include "toy/Standard.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/canvas/Texture.hpp"

namespace toy{
namespace canvas{
class Geometry;
class Image;
class Program;
class Brush;

namespace _detail{

class Brush
{
	public:

		Brush(){}
		virtual ~Brush(){}

		virtual void viewport(int x, int y, int width, int height)=0;
		virtual void viewport(int *width,int *height)=0;
		virtual void render(toy::canvas::Brush*,float diff)=0;
		virtual void setProjection(const math::Matrix4<float> & matrix)=0;
		virtual void setModelview( const math::Matrix4<float> & matrix)=0;
		virtual void setProjection(const float* matrix)=0;
		virtual void setModelview( const float* matrix)=0;
		virtual auto getModelview()->const math::Matrix4<float> & = 0;
		virtual auto newTexture(const toy::ImageBuffer &image)->::toy::canvas::Texture=0;

		//-------------------Basic-------------------
		virtual auto newTextureID(const toy::ImageBuffer &image)->uint32_t=0;
		virtual void delTextureID(uint32_t id)=0;
		virtual void setClearColor(float r, float g, float b, float a)=0;
		virtual void clear()=0;
		virtual void flush()=0;

	//--------------------------------private--------------------------------

		virtual void _useProgram(toy::canvas::Program *program)=0;
		virtual bool _isSameProgram(toy::canvas::Program *program)=0;

		virtual void _add(toy::canvas::Geometry*)=0;
		virtual void _del(toy::canvas::Geometry*)=0;
		virtual void _add(toy::canvas::Image*)=0;
		virtual void _del(toy::canvas::Image*)=0;
};

}}}
