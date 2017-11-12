
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Export.hpp"
#include "toy/graph/Array.hpp"

namespace toy{
namespace graph{
class  Brush;
class  Program;
struct GeometryPrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::graph::Brush>
#define TYPE_002 std::shared_ptr<::toy::graph::Program>
#define TYPE_003 struct ::toy::graph::GeometryPrivate*
#define TYPE_004 ::toy::graph::Array3<float>

namespace toy{
namespace graph{

class TOY_API_GRAPH Geometry
{
	public:

		Geometry(TYPE_001 ptr);
		~Geometry();

		void visible(bool show=true);
		bool isVisible() const;

		void setModel(TYPE_004 data);
		void setProgram(TYPE_002 program);
		auto getProgram()->TYPE_002;

	private:

		TYPE_003  _this  = nullptr;
		TYPE_001  _brush = nullptr;

	public:

		void _bind();
		void _render();
};

}}

#undef TYPE_004
#undef TYPE_003
#undef TYPE_002
#undef TYPE_001
