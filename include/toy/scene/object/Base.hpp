
#pragma once

//#include "toy/scene/Export.hpp"

namespace toy{
namespace scene{
namespace object{

//class TOY_API_SCENE Base
class Base
{
	public:

		Base(){}
		virtual ~Base(){}

		virtual void refresh(float diff)=0;

	private:

};

}}}
