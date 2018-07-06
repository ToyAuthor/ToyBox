
#pragma once


#include "toy/Environment.hpp"


#ifdef TOY_MSVC
	#pragma warning(disable:4251)
#endif


/*------------They defined at "ToyBox/cmake/toy_ProcessOptions.cmake"------------
#define TOY_OPTION_RELEASE              1   // Set it to 0, if you want to debug.
#define TOY_OPTION_DYNAMIC_LIBRARY      1   // It's only work on Windows, To build dynamic link library.
#define TOY_OPTION_USE_GLEW             1
*/


#define TOY_OPTION_ENABLE_ASSEMBLY      0
#define TOY_OPTION_CHECK                1   // Test and check error.
#define TOY_OPTION_CHECK_CAREFUL        1   // It spent more time to check error.



#if defined(TOY_MSVC) && defined(TOY_64_BIT) && TOY_OPTION_ENABLE_ASSEMBLY
	#error "Visual Studio is not support assembly language on 64 bit system."
#endif


#ifndef _UNICODE
#define _UNICODE    // "UNICODE" is defined at "ToyBox/include/toy/Windows.hpp"
#endif


//---------------To define TOY_API---------------start

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	// TOY_EXPORT defined at "ToyBox/source/CMakeLists.txt"
	#ifdef TOY_EXPORT
		#define TOY_API __declspec(dllexport)
	#else
		#define TOY_API __declspec(dllimport)
	#endif

#else
	#define TOY_API
#endif

//---------------To define TOY_API---------------end
