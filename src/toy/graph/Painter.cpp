#include "toy/graph/Brush.hpp"
#include "toy/graph/Painter.hpp"
#include "toy/graph/ModelBuffer.hpp"
#include "toy/graph/Image.hpp"

using namespace toy;
using namespace graph;

Painter::Painter()
{
	bool err = false;
	_brush = std::make_shared<toy::graph::Brush>(toy::WHATEVER,&err);

	if ( err==false )
	{
		toy::Oops(TOY_MARK);
		throw std::runtime_error("Painter can't build brush");
	}
}

Painter::Painter(std::shared_ptr<Brush> brush):_brush(brush)
{
	;
}

Painter::~Painter()
{
	;
}

auto Painter::brush()->std::shared_ptr<Brush>
{
	return _brush;
}

auto Painter::newTexture(const toy::ImageBuffer &image)->::toy::graph::Texture
{
	auto   texture = _brush->newTexture(image);

	/*
	 * Maybe I have to implement something like this.
	 * texture->addBrush(_brush);
	 */

	return texture;
}

auto Painter::newImage(float x, float y,float width,float height,toy::graph::Texture id)->std::shared_ptr<toy::graph::Image>
{
	std::vector<toy::graph::VertexBuffer>  vbuffer(4);

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

	toy::graph::ModelBuffer   modelBuffer(_brush);

	modelBuffer.setShape(vbuffer);
	modelBuffer.setIndices({0,2,1,0,3,2});

	auto   image = std::make_shared<toy::graph::Image>(_brush);

	image->setModel(modelBuffer);
	image->setTexture(id);

	return image;
}
