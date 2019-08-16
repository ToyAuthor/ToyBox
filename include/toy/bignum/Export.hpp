
#pragma once

#include "toy/CompilerConfig.hpp"

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	#ifdef TOY_EXPORT_BIGNUM
		#define TOY_API_BIGNUM __declspec(dllexport)
	#else
		#define TOY_API_BIGNUM __declspec(dllimport)
	#endif

#else
	#define TOY_API_BIGNUM
#endif
