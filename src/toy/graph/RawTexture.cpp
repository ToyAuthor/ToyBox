#include "toy/graph/Standard.hpp"
#include "toy/graph/RawTexture.hpp"


using namespace toy;
using namespace graph;

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
