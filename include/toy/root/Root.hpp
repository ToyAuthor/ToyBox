
#pragma once

#include <string>
#include "toy/root/Export.hpp"

namespace toy{


class TOY_API_ROOT Root
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
