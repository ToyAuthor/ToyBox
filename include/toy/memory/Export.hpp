#pragma once

#include "toy/Environment.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_MEMORY
		#define TOY_API_MEMORY __declspec(dllexport)
	#else
		#define TOY_API_MEMORY __declspec(dllimport)
	#endif

#else
	#define TOY_API_MEMORY
#endif
