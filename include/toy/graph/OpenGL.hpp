/*
 * Include this header file,
 * if you want to use native OpenGL API.
 */

#pragma once


#include "toy/Standard.hpp"
#include "toy/Windows.hpp"


#if defined(TOY_ANDROID)
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#else
	#if TOY_OPTION_USE_GLEW
		#include <GL/glew.h>

		#if defined(TOY_WINDOWS)
			#include <GL/wglew.h>
		#endif

		#if defined(TOY_LINUX)
			#include <GL/glxew.h>

			//--------Remove unnecessary macro that come from <GL/glxew.h>--------
			#ifdef None
				#undef None    // There is an other one defined at <SFML/Window/WindowStyle.hpp>.
			#endif
			#ifdef Bool
				#undef Bool    // There is an other one defined at <luapp/DataType.hpp>.
			#endif
		#endif
	#else
		#ifdef TOY_MAC
			#include <OpenGL/gl.h>
		#else
			#include <GL/gl.h>
		#endif
	#endif
#endif

#include <SFML/OpenGL.hpp>
