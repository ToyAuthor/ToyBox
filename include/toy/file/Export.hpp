#pragma once

#include "toy/Environment.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_FILE
		#define TOY_API_FILE __declspec(dllexport)
	#else
		#define TOY_API_FILE __declspec(dllimport)
	#endif

#else
	#define TOY_API_FILE
#endif
