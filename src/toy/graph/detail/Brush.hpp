
#pragma once

#include "toy/Standard.hpp"
#include "toy/math/Matrix4.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/graph/Texture.hpp"

namespace toy{
namespace graph{
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
		virtual void render(toy::graph::Brush*,float diff)=0;
		virtual void sorting()=0;
		virtual void setProjection(const toy::math::Matrix4<float> &matrix)=0;
		virtual void setModelview( const toy::math::Matrix4<float> &matrix)=0;
		virtual auto newTexture(const toy::ImageBuffer &image)->::toy::graph::Texture=0;

		//-------------------Basic-------------------
		virtual auto newTextureID(const toy::ImageBuffer &image)->uint32_t=0;
		virtual void delTextureID(uint32_t id)=0;
		virtual void setClearColor(float r, float g, float b, float a)=0;
		virtual void clear()=0;
		virtual void flush()=0;

	//--------------------------------private--------------------------------

		virtual void _useProgram(toy::graph::Program *program)=0;
		virtual bool _isSameProgram(toy::graph::Program *program)=0;

		virtual void _add(toy::graph::Geometry*)=0;
		virtual void _del(toy::graph::Geometry*)=0;
		virtual void _add(toy::graph::Image*)=0;
		virtual void _del(toy::graph::Image*)=0;
};

}}}
