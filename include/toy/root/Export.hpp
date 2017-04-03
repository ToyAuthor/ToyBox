#pragma once

#include "toy/Environment.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_ROOT
		#define TOY_API_ROOT __declspec(dllexport)
	#else
		#define TOY_API_ROOT __declspec(dllimport)
	#endif

#else
	#define TOY_API_ROOT
#endif
