
#pragma once

#include "toy/Standard.hpp"
#include "toy/ImageBuffer.hpp"
#include "toy/canvas/Export.hpp"
#include "toy/canvas/Texture.hpp"

namespace toy{
namespace canvas{
class  Brush;
struct CanvasPrivate;
}}

#define TYPE_001 std::shared_ptr<::toy::canvas::Brush>

namespace toy{
namespace canvas{

class TOY_API_CANVAS Canvas
{
	public:

		Canvas(TYPE_001 brush,const toy::ImageBuffer &image);
		~Canvas();

		void setImage(float positionX,float positionY,const toy::ImageBuffer &image);
		void getImage(float positionX,float positionY,toy::ImageBuffer *image);
		auto getTexture()->toy::canvas::Texture;

	private:

		std::unique_ptr<CanvasPrivate>   _this;
		TYPE_001                         _brush;
		toy::canvas::Texture             _texture;
};

}}

#undef TYPE_001
