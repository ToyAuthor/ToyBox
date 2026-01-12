#include "toy/graph/Brush.hpp"
#include "toy/graph/Image.hpp"
#include "toy/scene/object/Image.hpp"

namespace toy{
namespace scene{
namespace object{

struct ImagePrivate
{
	std::shared_ptr<toy::graph::Image>   image;
};

}}}


using namespace toy;
using namespace scene;
using namespace object;


Image::Image(std::shared_ptr<graph::Brush> brush,std::shared_ptr<toy::graph::Image> image):_this(new ImagePrivate)
{
	_brush = brush;
	_this->image = image;
}

Image::~Image()
{
	delete _this;
}

void Image::refresh(float diff)
{
	_this->image->_update(diff);
}

void Image::setPosition(float ,float ){}
/*
void Image::setPosition(float x,float y)
{
	auto   array = _this->image->getVertexArray();

	float   w = (*array)[6] - (*array)[0];
	float   h = (*array)[4] - (*array)[1];

	(*array)[0]  = x;
	(*array)[1]  = y;
	(*array)[3]  = x;
	(*array)[4]  = y+h;
	(*array)[6]  = x+w;
	(*array)[7]  = y+h;
	(*array)[9]  = x+w;
	(*array)[10] = y;
}*/

void Image::setSize(float ,float ){}
/*void Image::setSize(float w,float h)
{
	auto   array = _this->image->getVertexArray();

	float   x = (*array)[0];
	float   y = (*array)[1];

	(*array)[4] = y+h;
	(*array)[6] = x+w;
	(*array)[7] = y+h;
	(*array)[9] = x+w;
}*/

void Image::visible(bool show)
{
	_this->image->visible(show);
}

void Image::doPatrol(float x1,float y1,float x2,float y2)
{
	this->setPosition(x1,y1);

	auto   func = [x1,y1,x2,y2]( std::shared_ptr<toy::graph::Array3<float>> list1,
	                             std::shared_ptr<toy::graph::Array3<float>> list2,
	                             float diff)
	{
		float    dx = diff*(x1-x2)*0.3f;
		float    dy = diff*(y1-y2)*0.3f;

		(*list2)[0] = (*list1)[0] + dx;
		(*list2)[1] = (*list1)[1] + dy;

		(*list2)[3] = (*list1)[3] + dx;
		(*list2)[4] = (*list1)[4] + dy;

		(*list2)[6] = (*list1)[6] + dx;
		(*list2)[7] = (*list1)[7] + dy;

		(*list2)[9] = (*list1)[9] + dx;
		(*list2)[10]= (*list1)[10]+ dy;
	};

	_this->image->route(func);
}
