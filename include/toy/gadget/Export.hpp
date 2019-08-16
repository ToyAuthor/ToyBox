#pragma once

#include "toy/CompilerConfig.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_GADGET
		#define TOY_API_GADGET __declspec(dllexport)
	#else
		#define TOY_API_GADGET __declspec(dllimport)
	#endif

#else
	#define TOY_API_GADGET
#endif
