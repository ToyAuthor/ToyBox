#include "toy/canvas/Image.hpp"
#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Factory.hpp"

namespace toy{
namespace canvas{

struct ImagePrivate
{
	std::unique_ptr<toy::canvas::_detail::Image> detail;
};

}}

using namespace toy;
using namespace canvas;

Image::Image(std::shared_ptr<::toy::canvas::Brush> brush):
	Node(::toy::canvas::node::IMAGE),
	_this(new ImagePrivate),
	_brush(brush)
{
	_brush->_add(this);
	_this->detail.reset(_brush->_getFactory()->createImage(_brush));
}

Image::Image( std::shared_ptr<::toy::canvas::Brush> brush,
              float                                 x,
              float                                 y,
              float                                 width,
              float                                 height,
              toy::canvas::Texture                  id ):
	Node(::toy::canvas::node::IMAGE),
	_this(new ImagePrivate),
	_brush(brush)
{
	_brush->_add(this);
	_this->detail.reset(_brush->_getFactory()->createImage(_brush));

	std::vector<toy::canvas::VertexBuffer>  vbuffer(4);

	vbuffer[0].setPosition(x, y, 0);
	vbuffer[0].setVector(0.0,0.0,1.0);
	vbuffer[0].setTexture(0.0,0.0);

	vbuffer[1].setPosition(x, height+y, 0);
	vbuffer[1].setVector(0.0,0.0,1.0);
	vbuffer[1].setTexture(0.0,1.0);

	vbuffer[2].setPosition(width+x, height+y, 0);
	vbuffer[2].setVector(0.0,0.0,1.0);
	vbuffer[2].setTexture(1.0,1.0);

	vbuffer[3].setPosition(width+x, y, 0);
	vbuffer[3].setVector(0.0,0.0,1.0);
	vbuffer[3].setTexture(1.0,0.0);

	toy::canvas::ModelBuffer   modelBuffer(brush);

	modelBuffer.setShape(vbuffer);
	modelBuffer.setIndices({0,2,1,0,3,2});

	setModel(modelBuffer);
	setTexture(id);
}

Image::~Image()
{
	_brush->_del(this);
}

void Image::visible(bool show)
{
	_this->detail->visible(show);
}

bool Image::isVisible() const
{
	return _this->detail->isVisible();
}

void Image::setModel(const ::toy::canvas::ModelBuffer &data)
{
	_this->detail->setModel(_brush,data);
}

void Image::setTexture(::toy::canvas::Texture id)
{
	_this->detail->setTexture(id);
}

auto Image::getTexture(int index)->::toy::canvas::Texture
{
	return _this->detail->getTexture(index);
}

void Image::pushMoreTexture(::toy::canvas::Texture id)
{
	_this->detail->pushMoreTexture(id);
}

void Image::setProgram(std::shared_ptr<::toy::canvas::Program> program)
{
	_this->detail->setProgram(program);
}

auto Image::getProgram()->std::shared_ptr<::toy::canvas::Program>
{
	return _this->detail->getProgram();
}

void Image::_bind()
{
	_this->detail->bind(_brush);
}

void Image::_render(toy::canvas::Brush *brush,float diff)
{
	_this->detail->render(brush,diff);
}

void Image::_update(float diff)
{
	_this->detail->update(diff);
}

void Image::_setPosition(const float* data)
{
	_this->detail->setPosition(data);
}
