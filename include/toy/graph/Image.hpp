
#pragma once

#include "toy/Standard.hpp"
#include "toy/Math.hpp"
#include "toy/graph/Export.hpp"
#include "toy/graph/Array.hpp"
#include "toy/graph/Texture.hpp"
#include "toy/graph/ModelBuffer.hpp"

namespace toy{
namespace graph{
class  Brush;
class  Program;
struct ImagePrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::graph::Brush>
#define TYPE_002 std::shared_ptr<::toy::graph::Program>
#define TYPE_003 struct ::toy::graph::ImagePrivate*
#define TYPE_004 std::shared_ptr<::toy::graph::Array3<float>>
#define TYPE_005 ::toy::graph::Texture

namespace toy{
namespace graph{

class TOY_API_GRAPH Image
{
	public:

		Image(TYPE_001 ptr);
		~Image();

		void visible(bool show=true);
		bool isVisible() const;

		void setModel(const ::toy::graph::ModelBuffer &data);

		void setTexture(TYPE_005 id);
		auto getTexture(int index=0)->TYPE_005;
		void pushMoreTexture(TYPE_005 id);

		void setProgram(TYPE_002 program);
		auto getProgram()->TYPE_002;

		void route(   std::function<void(TYPE_004,TYPE_004,float)>);
		auto route()->std::function<void(TYPE_004,TYPE_004,float)>;

	private:

		TYPE_003    _this  = nullptr;
		TYPE_001    _brush = nullptr;

	public:

		void _bind();
		void _render(::toy::graph::Brush *brush,float diff);
		void _update(float diff);
};

}}

#undef TYPE_005
#undef TYPE_004
#undef TYPE_003
#undef TYPE_002
#undef TYPE_001
