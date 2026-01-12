#include "toy/graph/Program.hpp"
#include "toy/graph/detail/BrushA.hpp"
#include "toy/graph/detail/TextureA.hpp"

using namespace toy;
using namespace graph;
using namespace _detail;

BrushA::BrushA()
{
	;
}

BrushA::~BrushA()
{
	;
}

void BrushA::render(toy::graph::Brush *ptr,float diff)
{
	_mgr.render(ptr,diff);
}

void BrushA::sorting()
{
	_mgr.sorting();
}

void BrushA::setProjection(const math::Matrix4<float> &matrix)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf((const float*)matrix.data);
	glMatrixMode(GL_MODELVIEW);
}

void BrushA::setModelview(const math::Matrix4<float> &matrix)
{
	glLoadIdentity();
	glLoadMatrixf((const float*)matrix.data);
}

static void BindTexture(GLuint *obj,GLuint id)
{
	if ( *obj!=id )
	{
		*obj = id;
		glBindTexture( GL_TEXTURE_2D, id );
	}
}

inline static bool IsErrorExist()
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return texID;
}

auto BrushA::newTexture(const toy::ImageBuffer &map)->::toy::graph::Texture
{
	auto   id = NewTextureID( map.data(),
	                          map.width(),
	                          map.height(),
	                          map.format(),
	                          &_oldTextureID);

	auto   raw = std::make_shared<toy::graph::RawTexture>(id);
	auto   texture = std::make_shared<toy::graph::_detail::TextureA>(raw,nullptr);
	return texture;
}

auto BrushA::newTextureID(const toy::ImageBuffer &map)->uint32_t
{
	return NewTextureID( map.data(),
	                     map.width(),
	                     map.height(),
	                     map.format(),
	                     &_oldTextureID);
}

void BrushA::delTextureID(uint32_t id)
{
	glDeleteTextures( 1, &id );
}

void BrushA::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
}

void BrushA::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BrushA::flush()
{
	glFlush();
}

void BrushA::viewport(int x, int y, int width, int height)
{
	_width = width;
	_height = height;
	glViewport(x, y, width, height);
}

void BrushA::viewport(int *width,int *height)
{
	*width  = _width;
	*height = _height;
}

void BrushA::_useProgram(toy::graph::Program *program)
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

bool BrushA::_isSameProgram(toy::graph::Program *program)
{
	if ( _program==program )
	{
		return true;
	}
	return false;
}

void BrushA::_add(toy::graph::Geometry *obj)   { _mgr.add(obj);}
void BrushA::_del(toy::graph::Geometry *obj)   { _mgr.del(obj);}
void BrushA::_add(toy::graph::Image *obj)      { _mgr.add(obj);}
void BrushA::_del(toy::graph::Image *obj)      { _mgr.del(obj);}
