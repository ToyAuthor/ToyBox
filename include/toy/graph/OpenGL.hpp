
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

#if defined(TOY_MAC)
	#include <OpenGL/glu.h>
#elif defined(TOY_ANDROID)
	//#include <GLES/glu.h>   No such file. Oh no!
#else
	#include <GL/glu.h>
#endif
