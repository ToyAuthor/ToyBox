
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Export.hpp"
#include "toy/canvas/Node.hpp"
#include "toy/canvas/Array.hpp"

namespace toy{
namespace canvas{
class  Brush;
class  Program;
struct GeometryPrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::canvas::Brush>
#define TYPE_002 std::shared_ptr<::toy::canvas::Program>
#define TYPE_003 std::unique_ptr<::toy::canvas::GeometryPrivate>
#define TYPE_004 ::toy::canvas::Array3<float>

namespace toy{
namespace canvas{

class TOY_API_CANVAS Geometry : public ::toy::canvas::Node
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

		TYPE_003  _this;
		TYPE_001  _brush;

	public:

		void _bind();
		void _render();
};

}}

#undef TYPE_004
#undef TYPE_003
#undef TYPE_002
#undef TYPE_001
