
#pragma once

#include "toy/graph/Standard.hpp"
#include "toy/graph/detail/Image.hpp"
#include "toy/graph/Array.hpp"

namespace toy{
namespace graph{
class Brush;
class GcArrayBufferA;
class GcIndicesA;
class Program;
}}


#define F_ARRAY_PTR std::shared_ptr<::toy::graph::Array3<float>>
#define POS_FUNCTOR std::function<void(F_ARRAY_PTR,F_ARRAY_PTR,float)>
#define GEOMETRY_PTR std::shared_ptr<::toy::graph::GcArrayBufferA>
#define INDICES_PTR std::shared_ptr<::toy::graph::GcIndicesA>
#define PROGRAM_PTR std::shared_ptr<::toy::graph::Program>

namespace toy{
namespace graph{
namespace _detail{

class ImageA : public toy::graph::_detail::Image
{
	public:

		ImageA(std::shared_ptr<::toy::graph::Brush>);
		~ImageA();

		void visible(bool show);
		bool isVisible() const;

		void setModel(std::shared_ptr<::toy::graph::Brush> brush,const ::toy::graph::ModelBuffer &data);
		void setTexture(::toy::graph::Texture id);
		auto getTexture(int index)->::toy::graph::Texture;
		void pushMoreTexture(::toy::graph::Texture id);
		void setProgram(std::shared_ptr<::toy::graph::Program> program);
		auto getProgram()->std::shared_ptr<::toy::graph::Program>;

		void bind(std::shared_ptr<::toy::graph::Brush> brush);
		void render(toy::graph::Brush *brush,float diff);
		void update(float);

	private:

		struct ShaderPak
		{
			GLint            textureCoord = -1;
			GLint            texture0 = -1;
			GLint            texture1 = -1;
			GLint            textureCount = -1;
		};

		GEOMETRY_PTR          _vList = nullptr;     // Vertex array
		INDICES_PTR           _iList = nullptr;     // Indices
		Texture               _texture = nullptr;   // For GL_TEXTURE0
		PROGRAM_PTR           _program = nullptr;
		std::vector<Texture>  _multiTextureList = std::vector<Texture>(0);  // For GL_TEXTURE{1~n}
		ShaderPak             _var;
		bool                  _isVisible = false;
};



}}}

#undef PROGRAM_PTR
#undef INDICES_PTR
#undef GEOMETRY_PTR
#undef F_ARRAY_PTR
#undef POS_FUNCTOR
