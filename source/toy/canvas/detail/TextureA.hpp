
#pragma once

#include "toy/canvas/Texture.hpp"
#include "toy/canvas/RawTexture.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class TextureA : public toy::canvas::_Texture
{
	public:

		TextureA( std::shared_ptr<toy::canvas::RawTexture>    raw,
		          uint32_t                                    width,
		          uint32_t                                    height,
		          std::shared_ptr<toy::canvas::Array2<float>> textureCoord );

		~TextureA();

		auto create(std::shared_ptr<toy::canvas::Array2<float>> textureCoord)->std::shared_ptr<_Texture>;
		auto _data() const->const void*;
		auto _texcoord() const->const void*;
		auto width()const ->uint32_t;
		auto height()const ->uint32_t;

	private:

		std::shared_ptr<toy::canvas::RawTexture>     _rawTexture = nullptr;
		std::shared_ptr<toy::canvas::Array2<float>>  _textureCoordArray = nullptr;
		uint32_t                                     _width = 0;
		uint32_t                                     _height = 0;
};


}}}
