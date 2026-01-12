#include "toy/canvas/Program.hpp"
#include "toy/canvas/detail/BrushB.hpp"
#include "toy/canvas/detail/TextureA.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;

BrushB::BrushB()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

BrushB::~BrushB()
{
	;
}

void BrushB::render(toy::canvas::Brush *ptr,float diff)
{
	_mgr.render(ptr,diff);
}

void BrushB::setProjection(const math::Matrix4<float> & matrix)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(matrix.data);
	glMatrixMode(GL_MODELVIEW);
}

void BrushB::setModelview(const math::Matrix4<float> & matrix)
{
	glLoadIdentity();
	glLoadMatrixf(matrix.data);
}

void BrushB::setProjection(const float* matrix)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void BrushB::setModelview(const float* matrix)
{
	glLoadIdentity();
	std::memcpy(_matrixM.data ,matrix, 16*sizeof(float));
	glLoadMatrixf(matrix);
}

const math::Matrix4<float>& BrushB::getModelview()
{
	return _matrixM;
}

static void BindTexture(GLuint *obj,GLuint id)
{
	if ( *obj!=id )
	{
		*obj = id;
		glBindTexture( GL_TEXTURE_2D, id );
	}
}

static inline bool IsErrorExist()
{
	if ( glGetError()==GL_NO_ERROR )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

static GLuint NewTextureID( const uint8_t* data,
                            int32_t        width,
                            int32_t        height,
                            toy::Option    format,
                            GLuint         *obj )
{
	GLuint     texID;
	glGenTextures( 1, &texID );

	if ( texID==0 )
	{
		toy::Oops(TOY_MARK);
	}

	BindTexture(obj,texID);

	#if TOY_OPTION_CHECK
	if (IsErrorExist())
	{
		toy::Oops(TOY_MARK);
		return 0;
	}
	#endif

	switch (format)
	{
		case toy::RGBA:
			glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
			break;
		case toy::RGB:
			glTexImage2D( GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
			break;
		default:
			toy::Oops(TOY_MARK);  // Not support yet.
	}

	#if TOY_OPTION_CHECK
	if (IsErrorExist())
	{
		toy::Oops(TOY_MARK);
		return 0;
	}
	#endif

//	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );  // It's default status.
//	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return texID;
}

auto BrushB::newTexture(const toy::ImageBuffer &map)->::toy::canvas::Texture
{
	auto   id = NewTextureID( map.data(),
	                          map.width(),
	                          map.height(),
	                          map.format(),
	                          &_oldTextureID);

	auto   raw = std::make_shared<toy::canvas::RawTexture>(id);
	auto   texture = std::make_shared<toy::canvas::_detail::TextureA>(raw,map.width(),map.height(),nullptr);
	return texture;
}

auto BrushB::newTextureID(const toy::ImageBuffer &map)->uint32_t
{
	return NewTextureID( map.data(),
	                     map.width(),
	                     map.height(),
	                     map.format(),
	                     &_oldTextureID);
}

void BrushB::delTextureID(uint32_t id)
{
	glDeleteTextures( 1, &id );
}

void BrushB::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
}

void BrushB::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BrushB::flush()
{
	glFlush();
}

void BrushB::viewport(int x, int y, int width, int height)
{
	_width = width;
	_height = height;
	glViewport(x, y, width, height);
}

void BrushB::viewport(int *width,int *height)
{
	*width  = _width;
	*height = _height;
}

void BrushB::_useProgram(toy::canvas::Program *program)
{
	if ( program==nullptr )
	{
		if ( _program != nullptr )
		{
			_program = nullptr;
			glUseProgram(0);
		}
	}
	else
	{
		if ( _program != program )
		{
			_program = program;
			_program->_use();
		}
	}
}

bool BrushB::_isSameProgram(toy::canvas::Program *program)
{
	if ( _program==program )
	{
		return true;
	}
	return false;
}
