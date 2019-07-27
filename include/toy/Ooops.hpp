
#pragma once

#include "toy/CompilerConfig.hpp"
#include "toy/Mark.hpp"

#if TOY_OPTION_CHECK
	#if TOY_OPTION_RELEASE
		#include "toy/Log.hpp"
	#else
		#include "toy/Exception.hpp"
	#endif
#endif

namespace toy{

#if TOY_OPTION_CHECK
	#if TOY_OPTION_RELEASE
		static inline void Ooops(const char *file,int line){ toy::Log("%s:%d\n",file,line); }
	#else
		static inline void Ooops(const char *file,int line){ throw toy::Exception(file,line); }
	#endif
#else
	static inline void Ooops(const char*,int){}
#endif

}
