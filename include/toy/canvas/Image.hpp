
#pragma once

#include "toy/Standard.hpp"
#include "toy/Math.hpp"
#include "toy/canvas/Export.hpp"
#include "toy/canvas/Node.hpp"
#include "toy/canvas/Array.hpp"
#include "toy/canvas/Texture.hpp"
#include "toy/canvas/ModelBuffer.hpp"

namespace toy{
namespace canvas{
class  Brush;
class  Program;
class  Space;
struct ImagePrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::canvas::Brush>
#define TYPE_002 std::shared_ptr<::toy::canvas::Program>
#define TYPE_003 std::unique_ptr<::toy::canvas::ImagePrivate>
#define TYPE_004 std::shared_ptr<::toy::canvas::Array3<float>>
#define TYPE_005 ::toy::canvas::Texture
#define TYPE_006 std::shared_ptr<::toy::canvas::Space>

namespace toy{
namespace canvas{

class TOY_API_CANVAS Image : public ::toy::canvas::Node
{
	public:

		Image( TYPE_001 ptr);
		Image( TYPE_006 ptr);
		Image( TYPE_006            ptr,
		       float               x,
		       float               y,
		       float               width,
		       float               height,
		       toy::canvas::Texture id );
		Image( TYPE_001            ptr,
		       float               x,
		       float               y,
		       float               width,
		       float               height,
		       toy::canvas::Texture id );
		~Image();

		void visible(bool show=true);
		bool isVisible() const;
		void setModel(const ::toy::canvas::ModelBuffer &data);
		void setTexture(TYPE_005 id);
		// Return null pointer if failed.
		auto getTexture(int index=0)->TYPE_005;
		void pushMoreTexture(TYPE_005 id);
		void setProgram(TYPE_002 program);
		auto getProgram()->TYPE_002;

	private:

		TYPE_003    _this;
		TYPE_001    _brush;
		TYPE_006    _space;

	public:

		void _bind();
		void _render(::toy::canvas::Brush *brush,float diff);
		void _update(float diff);
		void _setPosition(const float* data);
};

}}

#undef TYPE_006
#undef TYPE_005
#undef TYPE_004
#undef TYPE_003
#undef TYPE_002
#undef TYPE_001
