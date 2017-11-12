#pragma once

#include "toy/Environment.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_GRAPH
		#define TOY_API_GRAPH __declspec(dllexport)
	#else
		#define TOY_API_GRAPH __declspec(dllimport)
	#endif

#else
	#define TOY_API_GRAPH
#endif
