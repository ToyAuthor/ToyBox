
#pragma once

#include "toy/graph/Texture.hpp"
#include "toy/graph/RawTexture.hpp"

namespace toy{
namespace graph{
namespace _detail{

class TextureA : public toy::graph::_Texture
{
	public:

		TextureA( std::shared_ptr<toy::graph::RawTexture>    raw,
		                std::shared_ptr<toy::graph::Array2<float>> textureCoord );

		~TextureA();

		auto create(std::shared_ptr<toy::graph::Array2<float>> textureCoord)->std::shared_ptr<_Texture>;
		auto _data() const->const void*;
		auto _texcoord() const->const void*;

	private:

		std::shared_ptr<toy::graph::RawTexture>      _rawTexture = nullptr;
		std::shared_ptr<toy::graph::Array2<float>>   _textureCoordArray = nullptr;

	//	std::shared_ptr<graph::Brush> _brush;    // Maybe I should keep it.
};


}}}
