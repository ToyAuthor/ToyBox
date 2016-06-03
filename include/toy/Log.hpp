
#pragma once


#include "toy/log/Printer.hpp"


namespace toy{

TOY_API void Log(const char *fmt, ... );
TOY_API void Log(const wchar_t *fmt, ... );
TOY_API void Log(const std::exception &);

#if TOY_OPTION_CHECK
	inline void Oops(const char *file,int line){ toy::Log("%s:%d\n",file,line); }
#else
	inline void Oops(const char*,int){}
#endif

}
