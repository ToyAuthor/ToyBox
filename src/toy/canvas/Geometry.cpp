#include "toy/canvas/Geometry.hpp"
#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Factory.hpp"


namespace toy{
namespace canvas{

struct GeometryPrivate
{
	std::unique_ptr<toy::canvas::_detail::Geometry> detail;
};

}}

using namespace toy;
using namespace canvas;

Geometry::Geometry(std::shared_ptr<toy::canvas::Brush> ptr):
	Node(::toy::canvas::node::GEOMETRY),
	_this(new GeometryPrivate),
	_brush(ptr)
{
	_brush->_add(this);
	_this->detail.reset(_brush->_getFactory()->createGeometry(ptr));
}

Geometry::~Geometry()
{
	_brush->_del(this);
}

void Geometry::visible(bool show)
{
	_this->detail->visible(show);
}

bool Geometry::isVisible() const
{
	return _this->detail->isVisible();
}

void Geometry::setModel(toy::canvas::Array3<float> data)
{
	_this->detail->setModel(_brush,data);
}

void Geometry::setProgram(std::shared_ptr<toy::canvas::Program> program)
{
	_this->detail->setProgram(program);
}

auto Geometry::getProgram()->std::shared_ptr<toy::canvas::Program>
{
	return _this->detail->getProgram();
}

void Geometry::_bind()
{
	_this->detail->bind(_brush);
}

void Geometry::_render()
{
	_this->detail->render();
}
