#include "toy/graph/detail/TextureA.hpp"

using namespace toy;
using namespace graph;
using namespace _detail;

TextureA::TextureA( std::shared_ptr<toy::graph::RawTexture>    raw,
		                        std::shared_ptr<toy::graph::Array2<float>> textureCoord )
{
	_rawTexture = raw;

	if ( textureCoord )
	{
		_textureCoordArray = textureCoord;
	}
}

TextureA::~TextureA()
{
	;
}

auto TextureA::create(std::shared_ptr<toy::graph::Array2<float>> textureCoord)->std::shared_ptr<_Texture>
{
	return std::make_shared<TextureA>(_rawTexture,textureCoord);
}

const void* TextureA::_data() const
{
	return static_cast<const void*>(_rawTexture->get());
}

const void* TextureA::_texcoord() const
{
	return static_cast<const void*>(_textureCoordArray->data());
}
