
#pragma once


#include "toy/Standard.hpp"
#include "toy/Windows.hpp"


#if ! defined(TOY_ANDROID)
	#include "GL/glew.h"

	#if defined(TOY_WINDOWS)
		#include "GL/wglew.h"
	#endif

	#if defined(TOY_LINUX)
		#include "GL/glxew.h"
	#endif
#endif

#include <SFML/OpenGL.hpp>
