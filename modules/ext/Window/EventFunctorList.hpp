
#pragma once

#include <functional>

struct EventFunctorList
{
	std::function<void(int,int)>     resize = [](int,int){};
};
