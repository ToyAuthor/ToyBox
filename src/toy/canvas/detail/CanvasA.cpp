#include "toy/canvas/Standard.hpp"
#include "toy/canvas/detail/CanvasA.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;

CanvasA::CanvasA()
{
	;
}

CanvasA::~CanvasA()
{
	;
}

static inline GLuint GetTextureID(toy::canvas::Texture tex)
{
	return *(static_cast<const GLuint*>(tex->_data()));
}

void CanvasA::setImage(float positionX,float positionY,const toy::ImageBuffer &image,toy::canvas::Texture tex)
{
	if ( image.format()!=toy::RGBA )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	int  x = positionX;
	int  y = positionY;

	glBindTexture( GL_TEXTURE_2D, GetTextureID(tex) );

	// glReadPixels( x, y, image.width(), image.height(), GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, image.width(), image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.data());
}

void CanvasA::getImage(float positionX,float positionY,toy::ImageBuffer *image,toy::canvas::Texture tex)
{
	int  x = positionX;
	int  y = positionY;

	if ( image->format()!=toy::RGBA )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	glBindTexture( GL_TEXTURE_2D, GetTextureID(tex) );

	glReadPixels( x, y, image->width(), image->height(), GL_RGBA, GL_UNSIGNED_BYTE, image->_data());
}
