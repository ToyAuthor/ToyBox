
#pragma once

#include "toy/CompilerConfig.hpp"
#include "toy/Mark.hpp"
#if TOY_OPTION_CHECK
#include "toy/Log.hpp"
#endif

namespace toy{

#if TOY_OPTION_CHECK
	static inline void Oops(const char *file,int line){ toy::Log("%s:%d\n",file,line); }
#else
	static inline void Oops(const char*,int){}
#endif

}
