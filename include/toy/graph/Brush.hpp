
#pragma once

#include "toy/Standard.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/Color.hpp"
#include "toy/math/Matrix4.hpp"
#include "toy/graph/Export.hpp"
#include "toy/graph/Texture.hpp"



namespace toy
{
	namespace graph
	{
		class Factory;
		class Program;
		class Geometry;
		class Image;
		struct BrushPrivate;
	}
}



namespace toy{
namespace graph{

/*
 * One program just has one brush(for now).
 * Basically, toy::graph::Brush is a wrapper of OpenGL.
 *
 * Not every method could work on all versions of OpenGL.
 */
class TOY_API_GRAPH Brush
{
	public:

		/*
		 * Make sure the OpenGL version not too old to you.
		 *
		 * Options:
		 *     toy::GL_4_5
		 *     toy::GL_4_4
		 *     ...
		 *     toy::GL_2_0
		 *     toy::WHATEVER
		 */
		Brush(enum toy::Option version,bool *isOK);
		~Brush();

		void viewport(int width, int height);
		void viewport(int *width,int *height);
		void viewport(int x, int y, int width, int height);
		// diff:the passing time since latest data update.
		void render(float diff = 0.0f);
		void sorting();
		void setProjection(const math::Matrix4<float> &matrix);
		void setModelview( const math::Matrix4<float> &matrix);
		auto newTexture(const toy::ImageBuffer &image)->::toy::graph::Texture;


		//-------------------Basic-------------------
		auto newTextureID(const toy::ImageBuffer &image)->uint32_t;
		void delTextureID(uint32_t id);
		void setClearColor(const toy::Color& color);
		void setClearColor(float r, float g, float b, float a);
		void clear();
		void flush();

	private:

		toy::graph::BrushPrivate*       _this = nullptr;

	public:

		auto _getFactory()->toy::graph::Factory*;

		void _useProgram(toy::graph::Program *program);
		bool _isSameProgram(toy::graph::Program *program);

		void _add(toy::graph::Geometry*);
		void _del(toy::graph::Geometry*);
		void _add(toy::graph::Image*);
		void _del(toy::graph::Image*);
};

}}
