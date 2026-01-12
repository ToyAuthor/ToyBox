#include "toy/graph/Geometry.hpp"
#include "toy/graph/Brush.hpp"
#include "toy/graph/Factory.hpp"


namespace toy{
namespace graph{

struct GeometryPrivate
{
	std::unique_ptr<toy::graph::_detail::Geometry> detail;
};

}}

using namespace toy;
using namespace graph;

Geometry::Geometry(std::shared_ptr<toy::graph::Brush> ptr):
	_this(new GeometryPrivate),
	_brush(ptr)
{
	_brush->_add(this);
	_this->detail.reset(_brush->_getFactory()->createGeometry());
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

void Geometry::setModel(toy::graph::Array3<float> data)
{
	_this->detail->setModel(_brush,data);
}

void Geometry::setProgram(std::shared_ptr<toy::graph::Program> program)
{
	_this->detail->setProgram(program);
}

auto Geometry::getProgram()->std::shared_ptr<toy::graph::Program>
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
