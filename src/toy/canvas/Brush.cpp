#include "toy/canvas/Standard.hpp"
#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Factory.hpp"

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

namespace toy{
namespace canvas{

struct BrushPrivate
{
	std::unique_ptr<toy::canvas::Factory>         factory;
	std::unique_ptr<toy::canvas::_detail::Brush>  detail;
};

static void InitBrushDevice(enum toy::Option option,::toy::canvas::BrushPrivate *obj)
{
	MakeSureOnlyOneBrushExist();

	toy::canvas::Factory*         factory = nullptr;

	if ( ! toy::canvas::CreateFactory(option,&factory) )
	{
		throw toy::Exception(TOY_MARK);
	}
	else
	{
		obj->factory.reset(factory);
		obj->detail.reset(obj->factory->createBrush());
	}
}

}}

using namespace toy;
using namespace canvas;

Brush::Brush(enum toy::Option option):_this(new BrushPrivate)
{
	InitBrushDevice(option,_this.get());
}

Brush::Brush():_this(new BrushPrivate)
{
	InitBrushDevice(toy::WHATEVER,_this.get());
}

Brush::~Brush()
{
	;
}

void Brush::render(float diff)
{
	_this->detail->render(this,diff);
}

void Brush::setProjection(const math::Matrix4<float> &matrix)
{
	_this->detail->setProjection(matrix);
}

void Brush::setModelview(const math::Matrix4<float> &matrix)
{
	_this->detail->setModelview(matrix);
}

auto Brush::newTexture(const toy::ImageBuffer &image)->::toy::canvas::Texture
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
	color.get(&r,&g,&b,&a);
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

void Brush::_useProgram(toy::canvas::Program *program)
{
	_this->detail->_useProgram(program);
}

bool Brush::_isSameProgram(toy::canvas::Program *program)
{
	return _this->detail->_isSameProgram(program);
}

void Brush::_add(toy::canvas::Geometry* ptr)
{
	_this->detail->_add(ptr);
}

void Brush::_del(toy::canvas::Geometry* ptr)
{
	_this->detail->_del(ptr);
}

void Brush::_add(toy::canvas::Image* ptr)
{
	_this->detail->_add(ptr);
}

void Brush::_del(toy::canvas::Image* ptr)
{
	_this->detail->_del(ptr);
}

auto Brush::_getFactory()->toy::canvas::Factory*
{
	return _this->factory.get();
}
