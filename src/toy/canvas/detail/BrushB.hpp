
#pragma once

#include "toy/canvas/detail/Brush.hpp"
#include "toy/canvas/detail/DataMgrB.hpp"

namespace toy{
namespace canvas{
namespace _detail{

/*
 * For OpenGL 2.0+ but 3.0
 */
class BrushB : public toy::canvas::_detail::Brush
{
	public:

		BrushB();
		~BrushB();

		void viewport(int x, int y, int width, int height);
		void viewport(int *width,int *height);
		void render(toy::canvas::Brush*,float diff);
		void setProjection(const math::Matrix4<float> & matrix);
		void setModelview( const math::Matrix4<float> & matrix);
		void setProjection(const float* matrix);
		void setModelview( const float* matrix);
		auto getModelview()->const math::Matrix4<float> &;
		auto newTexture(const toy::ImageBuffer &image)->::toy::canvas::Texture;

		//-------------------Basic-------------------
		auto newTextureID(const toy::ImageBuffer &image)->uint32_t;
		void delTextureID(uint32_t id);
		void setClearColor(float r, float g, float b, float a);
		void clear();
		void flush();

	private:

		toy::canvas::Program*          _program = nullptr;
		toy::canvas::_detail::DataMgrB _mgr;
		GLuint                         _oldTextureID = 0;
		int                            _width = 0;
		int                            _height = 0;
		toy::math::Matrix4<float>      _matrixM;   // Modelview

	public:

		void _useProgram(toy::canvas::Program *program);
		bool _isSameProgram(toy::canvas::Program *program);

		void _add(toy::canvas::Geometry *obj)   { _mgr.add(obj);}
		void _del(toy::canvas::Geometry *obj)   { _mgr.del(obj);}
		void _add(toy::canvas::Image *obj)      { _mgr.add(obj);}
		void _del(toy::canvas::Image *obj)      { _mgr.del(obj);}
};

}}}
