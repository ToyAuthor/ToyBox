
#pragma once

#include "toy/Standard.hpp"
#include "toy/scene/Export.hpp"
#include "toy/File.hpp"



namespace toy{
namespace scene{

class TOY_API_SCENE Scene
{
	public:

		Scene();
		~Scene();

		void render();

	//	auto newObject(toy::File io,scene::ObjectType,"Model.dat")->std::shared_ptr<>;

	private:

};

}}
