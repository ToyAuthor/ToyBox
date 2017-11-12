#include "toy/graph/Image.hpp"
#include "toy/graph/Brush.hpp"
#include "toy/graph/Factory.hpp"

namespace toy{
namespace graph{

struct ImagePrivate
{
	toy::graph::_detail::Image*  detail = nullptr;
};

}}

using namespace toy;
using namespace graph;

Image::Image(std::shared_ptr<::toy::graph::Brush> brush):
	_this(new ImagePrivate),
	_brush(brush)
{
	_brush->_add(this);
	_this->detail = _brush->_getFactory()->createImage(_brush);
}

Image::~Image()
{
	_brush->_del(this);
	delete _this->detail;
	delete _this;
}

void Image::visible(bool show)
{
	_this->detail->visible(show);
}

bool Image::isVisible() const
{
	return _this->detail->isVisible();
}

void Image::setModel(const ::toy::graph::ModelBuffer &data)
{
	_this->detail->setModel(_brush,data);
}

void Image::setTexture(::toy::graph::Texture id)
{
	_this->detail->setTexture(id);
}

auto Image::getTexture(int index)->::toy::graph::Texture
{
	return _this->detail->getTexture(index);
}

void Image::pushMoreTexture(::toy::graph::Texture id)
{
	_this->detail->pushMoreTexture(id);
}

void Image::setProgram(std::shared_ptr<::toy::graph::Program> program)
{
	_this->detail->setProgram(program);
}

auto Image::getProgram()->std::shared_ptr<::toy::graph::Program>
{
	return _this->detail->getProgram();
}

void Image::route( std::function<void( std::shared_ptr<::toy::graph::Array3<float>>,
                                       std::shared_ptr<::toy::graph::Array3<float>>,
                                       float )> func)
{
	(void)func;
}

auto Image::route()->std::function<void( std::shared_ptr<::toy::graph::Array3<float>>,
                                         std::shared_ptr<::toy::graph::Array3<float>>,
                                         float)>
{
	return {};
}

void Image::_bind()
{
	_this->detail->bind(_brush);
}

void Image::_render(toy::graph::Brush *brush,float diff)
{
	_this->detail->render(brush,diff);
}

void Image::_update(float diff)
{
	_this->detail->update(diff);
}
