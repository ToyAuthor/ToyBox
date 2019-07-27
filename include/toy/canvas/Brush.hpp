
#pragma once

#include "toy/Standard.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/Color.hpp"
#include "toy/canvas/Export.hpp"
#include "toy/canvas/Texture.hpp"

namespace toy
{
	namespace canvas
	{
		class Factory;
		class Program;
		class Geometry;
		class Image;
		struct BrushPrivate;
	}
}

namespace toy{
namespace canvas{

/*
 * One program just has one brush(for now).
 * Basically, toy::canvas::Brush is a wrapper of OpenGL.
 *
 * Not every method could work on all versions of OpenGL.
 */
class TOY_API_CANVAS Brush
{
	public:

		/*
		 * 1.Create a render device,
		 * 2.Make sure the OpenGL version not too old to your expectation.(optional)
		 *
		 * Options:
		 *     toy::GL_3_0
		 *     toy::GL_2_0
		 *     toy::WHATEVER    Let toy::canvas::Brush choose OpenGL version by itself.
		 */
		Brush(enum toy::Option expectVersion);
		Brush();
		~Brush();

		void viewport(int width, int height);
		void viewport(int *width,int *height);
		void viewport(int x, int y, int width, int height);
		// diff:the passing time since latest data update.
		void render(float diff = 0.0f);
		void setProjection(const toy::math::Matrix4<float> &matrix);
		void setModelview( const toy::math::Matrix4<float> &matrix);
		auto newTexture(const toy::ImageBuffer &image)->::toy::canvas::Texture;

		//-------------------Basic-------------------
		auto newTextureID(const toy::ImageBuffer &image)->uint32_t;
		void delTextureID(uint32_t id);
		void setClearColor(const toy::Color& color);
		void setClearColor(float r, float g, float b, float a);
		void clear();
		void flush();

	private:

		std::unique_ptr<toy::canvas::BrushPrivate>       _this;

	public:

		auto _getFactory()->toy::canvas::Factory*;

		void _useProgram(toy::canvas::Program *program);
		bool _isSameProgram(toy::canvas::Program *program);

		//-------------- DataMgr* handle following method --------------
		void _add(toy::canvas::Geometry*);
		void _del(toy::canvas::Geometry*);
		void _add(toy::canvas::Image*);
		void _del(toy::canvas::Image*);
};

}}
