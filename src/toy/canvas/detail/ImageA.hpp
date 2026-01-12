
#pragma once

#include <atomic>
#include "toy/canvas/Standard.hpp"
#include "toy/canvas/detail/Image.hpp"
#include "toy/canvas/Array.hpp"

namespace toy{
namespace canvas{
namespace _detail{
class GcArrayBufferA;
class GcIndicesA;
}}}

#define BRUSH_PTR    std::shared_ptr<::toy::canvas::Brush>
#define F_ARRAY_PTR  std::shared_ptr<::toy::canvas::Array3<float>>
#define GEOMETRY_PTR std::shared_ptr<::toy::canvas::_detail::GcArrayBufferA>
#define INDICES_PTR  std::shared_ptr<::toy::canvas::_detail::GcIndicesA>
#define PROGRAM_PTR  std::shared_ptr<::toy::canvas::Program>

namespace toy{
namespace canvas{
namespace _detail{

class ImageA : public toy::canvas::_detail::Image
{
	public:

		ImageA(BRUSH_PTR);
		~ImageA();

		void visible(bool show);
		bool isVisible() const;

		void setModel(BRUSH_PTR brush,const ::toy::canvas::ModelBuffer &data);
		void setTexture(::toy::canvas::Texture id);
		auto getTexture(int index)->::toy::canvas::Texture;
		void pushMoreTexture(::toy::canvas::Texture id);
		void setProgram(PROGRAM_PTR program);
		auto getProgram()->PROGRAM_PTR;

		void bind(BRUSH_PTR brush);
		void render(toy::canvas::Brush *brush,float diff);
		void update(float);
		void setPosition(const float* data);

	private:

		struct ShaderPak
		{
			GLint            textureCoord = -1;
			GLint            texture0 = -1;
			GLint            texture1 = -1;
			GLint            textureCount = -1;
		};

		GEOMETRY_PTR                  _vList = nullptr;     // Vertex array
		INDICES_PTR                   _iList = nullptr;     // Indices
		Texture                       _texture = nullptr;   // For GL_TEXTURE0
		PROGRAM_PTR                   _program = nullptr;
		std::vector<Texture>          _multiTextureList;    // For GL_TEXTURE{1~n}
		ShaderPak                     _var;
		bool                          _isVisible = false;
};

}}}

#undef PROGRAM_PTR
#undef INDICES_PTR
#undef GEOMETRY_PTR
#undef F_ARRAY_PTR
#undef BRUSH_PTR
