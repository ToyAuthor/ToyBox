#include "toy/canvas/Standard.hpp"
#include "toy/canvas/RawTexture.hpp"

using namespace toy;
using namespace canvas;

RawTexture::RawTexture(const GLuint id):_id(id)
{
	;
}

RawTexture::~RawTexture()
{
	glDeleteTextures( 1, &_id );
}

const GLuint* RawTexture::get() const
{
	return &_id;
}
