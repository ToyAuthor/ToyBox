
#pragma once

#include <functional>
#include "toy/log/Printer.hpp"

#define TOY_OPTION_ENABLE_PLUGIN_LOG_SYSTEM 1

namespace toy{

TOY_API void Log(const char *fmt, ... );
TOY_API void Log(const wchar_t *fmt, ... );
TOY_API void Log(const std::exception &);

#if TOY_OPTION_ENABLE_PLUGIN_LOG_SYSTEM

namespace log{
TOY_API void PushDevice(std::function<void(const char*)>,std::function<void(const wchar_t*)>);
TOY_API void PopDevice();
TOY_API void BackDefaultDevice();
}

#endif

#if TOY_OPTION_CHECK
	inline void Oops(const char *file,int line){ toy::Log("%s:%d\n",file,line); }
#else
	inline void Oops(const char*,int){}
#endif

}
