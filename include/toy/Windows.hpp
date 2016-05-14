
#pragma once

#include "toy/CompilerConfig.hpp"

#ifdef TOY_WINDOWS

	#ifndef UNICODE
	#define UNICODE
	#endif

	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif

	#include <windows.h>

	#ifdef TOY_MSVC
		#pragma comment(lib,"user32.lib")
		#pragma comment(lib,"kernel32.lib")
	#endif

#endif
