#pragma once

#include "toy/CompilerConfig.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_CANVAS
		#define TOY_API_CANVAS __declspec(dllexport)
	#else
		#define TOY_API_CANVAS __declspec(dllimport)
	#endif

#else
	#define TOY_API_CANVAS
#endif
