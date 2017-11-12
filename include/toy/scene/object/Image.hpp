
#pragma once

#include <memory>
#include "toy/scene/Export.hpp"
#include "toy/scene/object/Common.hpp"

namespace toy{
	namespace graph
	{
		class Image;
	}

namespace scene{
namespace object{

struct ImagePrivate;

class TOY_API_SCENE Image : public ::toy::scene::object::Base
{
	public:

		Image(std::shared_ptr<graph::Brush>,std::shared_ptr<toy::graph::Image>);
		~Image();

		void refresh(float diff);

		void setPosition(float x,float y);
		void setSize(float w,float h);
		void visible(bool show=true);
		void doPatrol(float x1,float y1,float x2,float y2);

	private:

		ImagePrivate*                   _this = nullptr;
		std::shared_ptr<graph::Brush>   _brush = nullptr;
};


}}}
