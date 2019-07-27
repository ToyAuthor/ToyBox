#include "toy/canvas/detail/TextureA.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;

TextureA::TextureA( std::shared_ptr<toy::canvas::RawTexture>    raw,
                    uint32_t                                    width,
                    uint32_t                                    height,
                    std::shared_ptr<toy::canvas::Array2<float>> textureCoord )
:_rawTexture(raw),_width(width),_height(height)
{
	if ( textureCoord )
	{
		_textureCoordArray = textureCoord;
	}
}

TextureA::~TextureA()
{
	;
}

auto TextureA::create(std::shared_ptr<toy::canvas::Array2<float>> textureCoord)->std::shared_ptr<_Texture>
{
	return std::make_shared<TextureA>(_rawTexture,_width,_height,textureCoord);
}

const void* TextureA::_data() const
{
	return static_cast<const void*>(_rawTexture->get());
}

const void* TextureA::_texcoord() const
{
	return static_cast<const void*>(_textureCoordArray->data());
}

uint32_t TextureA::width()const
{
	return _width;
}

uint32_t TextureA::height()const
{
	return _height;
}
