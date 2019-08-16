#pragma once

#include "toy/CompilerConfig.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_TIME
		#define TOY_API_TIME __declspec(dllexport)
	#else
		#define TOY_API_TIME __declspec(dllimport)
	#endif

#else
	#define TOY_API_TIME
#endif
