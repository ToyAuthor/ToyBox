#include "toy/graph/Brush.hpp"
#include "toy/graph/Painter.hpp"
#include "toy/scene/Scene.hpp"

using namespace toy;

Scene::Scene(std::shared_ptr<graph::Painter> pen):_painter(pen)
{
	;
}

Scene::Scene():_painter(std::make_shared<toy::graph::Painter>())
{
	;
}

Scene::~Scene()
{
	;
}

auto Scene::brush()->std::shared_ptr<graph::Brush>
{
	return _painter->brush();
}

void Scene::render()
{
	_painter->brush()->render();
}

void Scene::setCamera(const toy::scene::CameraConfig &camera)
{
	_painter->brush()->setProjection( camera.projection() );
	_painter->brush()->setModelview( camera.modelview() );
}

auto Scene::newObject(scene::IMAGE_T,const toy::ImageBuffer &raw)->std::shared_ptr<toy::scene::object::Image>
{
	auto    brush = _painter->brush();

	auto    texture = brush->newTexture(raw);

	auto    image = _painter->newImage(0, 0,raw.width(),raw.height(),texture);

	auto    obj = std::make_shared<toy::scene::object::Image>(brush,image);

	return obj;
}
