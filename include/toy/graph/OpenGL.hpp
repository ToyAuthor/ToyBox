
#pragma once


#include "toy/Standard.hpp"
#include "toy/Windows.hpp"


#include "GL/glew.h"

#if defined(TOY_WINDOWS)
	#include "GL/wglew.h"
#endif

#if defined(TOY_LINUX)
	#include "GL/glxew.h"
#endif

#include <SFML/OpenGL.hpp>

#if defined(TOY_MAC)
	#include <OpenGL/glu.h>
#else
	#include <GL/glu.h>
#endif
