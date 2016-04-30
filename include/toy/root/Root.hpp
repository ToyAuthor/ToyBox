
#pragma once

#include "toy/Standard.hpp"


namespace toy{


class TOY_API Root
{
	public:

		Root();
		~Root();

		static std::string  GetVersion();
		static std::string  GetPlatform();
		static std::string  GetComment();
};


}//namespace toy
