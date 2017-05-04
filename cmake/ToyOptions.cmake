
macro(toy_ProcessOptions)

	if(TOY_RELEASE)
		add_definitions(-DTOY_OPTION_RELEASE=1)
	else()
		add_definitions(-DTOY_OPTION_RELEASE=0)
	endif()

	if(TOY_ENABLE_SHARED_LIBS)
		set(TOY_LIB_TYPE SHARED)
		add_definitions(-DTOY_OPTION_DYNAMIC_LIBRARY=1)
	else()
		set(TOY_LIB_TYPE STATIC)
		add_definitions(-DTOY_OPTION_DYNAMIC_LIBRARY=0)
	endif()

	list(APPEND TOY_DEFAULT_INCLUDE_DIR ${TOY_include_boost})
	list(APPEND TOY_DEFAULT_INCLUDE_DIR ${TOY_include_sfml})
	list(APPEND TOY_DEFAULT_LINK_DIR    ${TOY_library_boost})
	list(APPEND TOY_DEFAULT_LINK_DIR    ${TOY_library_sfml})

	if(WIN32)
		# _WIN32_WINNT 0x0A00 Windows 10
		# _WIN32_WINNT 0x0603 Windows 8.1
		# _WIN32_WINNT 0x0602 Windows 8
		# _WIN32_WINNT 0x0601 Windows 7
		# _WIN32_WINNT 0x0600 Windows Vista
		# _WIN32_WINNT 0x0501 Windows XP
		# _WIN32_WINNT 0x0500 Windows 2000
		# _WIN32_WINNT 0x0410 Windows 98
		# _WIN32_WINNT 0x0400 Windows 95
		# Boost need this to build library on Windows 2000 or later releases.
		add_definitions(-D_WIN32_WINNT=0x0501)
	endif()

endmacro(toy_ProcessOptions)
