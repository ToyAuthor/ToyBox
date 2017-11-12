
#pragma once

#include "toy/graph/detail/Geometry.hpp"


namespace toy{
namespace graph{
class GcArrayBufferA;
}}

#define PROGRAM_PTR std::shared_ptr<toy::graph::Program>
#define GEOMETRY_PTR std::shared_ptr<::toy::graph::GcArrayBufferA>

namespace toy{
namespace graph{
namespace _detail{

class GeometryA : public toy::graph::_detail::Geometry
{
	public:

		GeometryA();
		~GeometryA();

		void visible(bool show);
		bool isVisible() const;

		void setModel(std::shared_ptr<toy::graph::Brush> brush,toy::graph::Array3<float> data);
		void setProgram(std::shared_ptr<toy::graph::Program> program);
		auto getProgram()->std::shared_ptr<toy::graph::Program>;

		void bind(std::shared_ptr<toy::graph::Brush> brush);
		void render();

	private:

		std::vector<float>   _data;
	//	GLuint               _vertexArrayID = 0;
		GEOMETRY_PTR         _vList = nullptr;
		PROGRAM_PTR          _program = nullptr;
		bool                 _isVisible = false;
};

}}}

#undef GEOMETRY_PTR
#undef PROGRAM_PTR
