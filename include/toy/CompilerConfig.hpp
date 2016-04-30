
#pragma once


#include "toy/EnvironmentalMacro.hpp"


#if defined(TOY_MSVC)
	#pragma warning(disable:4251)
#endif


/*
------------They defined by CMake now------------start
See "ToyBox/cmake/ToyOptions.cmake"

#define TOY_OPTION_RELEASE              1   // Set it to 0, if you want to debug.
#define TOY_OPTION_DYNAMIC_LIBRARY      1   // It's only work on Windows, To build dynamic link library.

------------They defined by CMake now------------end
*/


#define TOY_OPTION_ENABLE_ASSEMBLY      1
#define TOY_OPTION_CHECK                1   // Test and check error.
#define TOY_OPTION_CHECK_CAREFUL        1   // It spent more time to check error.
#define TOY_OPTION_USING_MSVC_LINK      0   // Add "#pragma comment(lib,"*.lib")" to link some library.


// Visual Studio on 64 bit is not support assembly language.
#if defined(TOY_MSVC) && defined(TOY_64_BIT)
	#undef  TOY_OPTION_ENABLE_ASSEMBLY
	#define TOY_OPTION_ENABLE_ASSEMBLY      0
#endif


#if TOY_OPTION_RELEASE
	#undef  TOY_OPTION_CHECK_CAREFUL
	#define TOY_OPTION_CHECK_CAREFUL        0
#endif


#define _UNICODE    // "UNICODE" is define at "ToyBox/source/toy/Windows.hpp"



//---------------To define TOY_API---------------start

#if defined(TOY_WINDOWS) && TOY_OPTION_DYNAMIC_LIBRARY

	// TOY_EXPORT defined at "ToyBox/source/toy/CMakeLists.txt"
	#ifdef TOY_EXPORT
		#define TOY_API __declspec(dllexport)
	#else
		#define TOY_API __declspec(dllimport)
	#endif

#else
	#define TOY_API
#endif

//---------------To define TOY_API---------------end


//-----------------------------Option check-----------------------------start

#if !defined(TOY_MSVC) && TOY_OPTION_USING_MSVC_LINK
	#error "It's not Visual Studio. Please set TOY_OPTION_USING_MSVC_LINK to 0"
#endif

//-----------------------------Option check-----------------------------end
