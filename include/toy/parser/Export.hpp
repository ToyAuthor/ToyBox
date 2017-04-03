#pragma once

#include "toy/Environment.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_PARSER
		#define TOY_API_PARSER __declspec(dllexport)
	#else
		#define TOY_API_PARSER __declspec(dllimport)
	#endif

#else
	#define TOY_API_PARSER
#endif
