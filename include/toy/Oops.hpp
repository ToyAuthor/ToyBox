
#pragma once

#include "toy/CompilerConfig.hpp"
#include "toy/Log.hpp"
#include "toy/Mark.hpp"

namespace toy{

#if TOY_OPTION_CHECK
	inline void Oops(const char *file,int line){ toy::Log("%s:%d\n",file,line); }
#else
	inline void Oops(const char*,int){}
#endif

}
