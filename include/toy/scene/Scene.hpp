
#pragma once

#include "toy/Standard.hpp"
#include "toy/scene/Export.hpp"
#include "toy/File.hpp"
#include "toy/ImageBuffer.hpp"

#include "toy/scene/CameraConfig.hpp"
#include "toy/scene/Option.hpp"
#include "toy/scene/object/Image.hpp"


namespace toy
{
	namespace graph
	{
		class Brush;
		class Painter;
	}
}


namespace toy{

class TOY_API_SCENE Scene
{
	public:

		Scene(std::shared_ptr<graph::Painter>);
		Scene();
		~Scene();

		auto brush()->std::shared_ptr<graph::Brush>;

		void render();

		void setCamera(const toy::scene::CameraConfig &camera);

		auto newObject(toy::scene::IMAGE_T,const toy::ImageBuffer &image)->std::shared_ptr<toy::scene::object::Image>;

	//	auto newObject(toy::graph::Texture handle)->std::shared_ptr<toy::scene::object::Image>;

	//	auto newObject(toy::File io,scene::ObjectType,"Model.dat")->std::shared_ptr<>;

	private:

		std::shared_ptr<graph::Painter>   _painter = nullptr;
};

}
