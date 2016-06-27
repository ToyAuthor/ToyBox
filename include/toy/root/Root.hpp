
#pragma once

#include "toy/Standard.hpp"


namespace toy{


class TOY_API Root
{
	public:

		Root();
		~Root();

		static std::string  GetVersion();
		static std::string  GetSystemType();
		static std::string  GetOperatingSystem();
		static std::string  GetComplierName();
		static std::string  GetPlatform();
		static std::string  GetComment();
};


}//namespace toy
