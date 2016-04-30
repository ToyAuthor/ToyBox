
#pragma once

#include "toy/Mark.hpp"

namespace toy{


// Use it to throw a simple exception.
struct Exception
{
	Exception(const char *str,int num):message(str),line(num){}

	const char*   message;
	int           line;
};


}//namespace toy
