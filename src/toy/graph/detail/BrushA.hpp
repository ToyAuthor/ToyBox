
#pragma once

#include "toy/graph/detail/Brush.hpp"
#include "toy/graph/DataMgrA.hpp"

namespace toy{
namespace graph{
namespace _detail{

/*
 * For OpenGL 3.0+
 */
class BrushA : public toy::graph::_detail::Brush
{
	public:

		BrushA();
		~BrushA();

		void viewport(int x, int y, int width, int height);
		void viewport(int *width,int *height);
		void render(toy::graph::Brush*,float diff);
		void sorting();
		void setProjection(const toy::math::Matrix4<float> &matrix);
		void setModelview( const toy::math::Matrix4<float> &matrix);
		auto newTexture(const toy::ImageBuffer &image)->::toy::graph::Texture;

		//-------------------Basic-------------------
		auto newTextureID(const toy::ImageBuffer &image)->uint32_t;
		void delTextureID(uint32_t id);
		void setClearColor(float r, float g, float b, float a);
		void clear();
		void flush();

	private:

		toy::graph::Program*    _program = nullptr;
		toy::graph::DataMgrA    _mgr;
		GLuint                  _oldTextureID = 0;
		int                     _width = 0;
		int                     _height = 0;

	public:

		void _useProgram(toy::graph::Program *program);
		bool _isSameProgram(toy::graph::Program *program);

		void _add(toy::graph::Geometry*);
		void _del(toy::graph::Geometry*);
		void _add(toy::graph::Image*);
		void _del(toy::graph::Image*);
};

}}}
