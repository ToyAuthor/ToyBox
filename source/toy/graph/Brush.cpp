#include "toy/graph/Standard.hpp"
#include "toy/graph/Brush.hpp"
#include "toy/graph/Factory.hpp"

static void MakeSureOnlyOneBrushExist()
{
	static bool first_time = true;

	if ( first_time==false )
	{
		toy::Oops(TOY_MARK);
	}
	else
	{
		first_time = false;
	}
}

template <typename T>
inline static void SafeDelete(T *ptr)
{
	if ( ptr!=nullptr )
	{
		delete ptr;
	}
}

namespace toy{
namespace graph{

struct BrushPrivate
{
	toy::graph::Factory*         factory = nullptr;
	toy::graph::_detail::Brush*  detail  = nullptr;
};

}}

using namespace toy;
using namespace graph;

Brush::Brush(enum toy::Option option,bool *result):_this(new BrushPrivate)
{
	MakeSureOnlyOneBrushExist();
	*result = true;

	if ( ! toy::graph::CreateFactory(option,&(_this->factory)) )
	{
		toy::Oops(TOY_MARK);
		*result = false;
	}
	else
	{
		_this->detail = _this->factory->createBrush();
	}
}

Brush::~Brush()
{
	SafeDelete(_this->detail);
	SafeDelete(_this->factory);

	delete _this;
}

void Brush::render(float diff)
{
	_this->detail->render(this,diff);
}

void Brush::sorting()
{
	_this->detail->sorting();
}

void Brush::setProjection(const math::Matrix4<float> &matrix)
{
	_this->detail->setProjection(matrix);
}

void Brush::setModelview(const math::Matrix4<float> &matrix)
{
	_this->detail->setModelview(matrix);
}

auto Brush::newTexture(const toy::ImageBuffer &image)->::toy::graph::Texture
{
	return _this->detail->newTexture(image);
}

auto Brush::newTextureID(const toy::ImageBuffer &image)->uint32_t
{
	return _this->detail->newTextureID(image);
}

void Brush::delTextureID(uint32_t id)
{
	_this->detail->delTextureID(id);
}

void Brush::setClearColor(float r, float g, float b, float a)
{
	_this->detail->setClearColor(r,g,b,a);
}

void Brush::setClearColor(const toy::Color& color)
{
	float r,g,b,a;
	color.data(&r,&g,&b,&a);
	_this->detail->setClearColor(r,g,b,a);
}

void Brush::clear()
{
	_this->detail->clear();
}

void Brush::flush()
{
	_this->detail->flush();
}

void Brush::viewport(int x, int y, int width, int height)
{
	_this->detail->viewport(x,y,width,height);
}

void Brush::viewport(int width, int height)
{
	_this->detail->viewport(0,0,width,height);
}

void Brush::viewport(int *width,int *height)
{
	_this->detail->viewport(width,height);
}

void Brush::_useProgram(toy::graph::Program *program)
{
	_this->detail->_useProgram(program);
}

bool Brush::_isSameProgram(toy::graph::Program *program)
{
	return _this->detail->_isSameProgram(program);
}

void Brush::_add(toy::graph::Geometry* ptr)
{
	_this->detail->_add(ptr);
}

void Brush::_del(toy::graph::Geometry* ptr)
{
	_this->detail->_del(ptr);
}

void Brush::_add(toy::graph::Image* ptr)
{
	_this->detail->_add(ptr);
}

void Brush::_del(toy::graph::Image* ptr)
{
	_this->detail->_del(ptr);
}

auto Brush::_getFactory()->toy::graph::Factory*
{
	return _this->factory;
}
