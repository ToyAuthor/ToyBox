
#pragma once

#include "toy/Standard.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/graph/Export.hpp"
#include "toy/graph/Texture.hpp"

namespace toy{
namespace graph{
class Brush;
class Image;
}}

#define TYPE_001 std::shared_ptr<::toy::graph::Brush>
#define TYPE_002 std::shared_ptr<::toy::graph::Image>

namespace toy{
namespace graph{

// A auxiliary for toy::graph::Brush.
class TOY_API_GRAPH Painter
{
	public:

		Painter(TYPE_001 brush);
		Painter();
		~Painter();

		auto brush()->TYPE_001;
		auto newTexture(const toy::ImageBuffer &image)->::toy::graph::Texture;
		auto newImage( float x,
		               float y,
		               float width,
		               float height,
		               toy::graph::Texture
		               )->TYPE_002;

	private:

		TYPE_001   _brush = nullptr;
};

}}

#undef TYPE_002
#undef TYPE_001
