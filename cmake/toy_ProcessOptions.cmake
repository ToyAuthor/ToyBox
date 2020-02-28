
macro(toy_ProcessOptions)

	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(TOY_RELEASE ON)
	else()
		set(TOY_RELEASE OFF)
	endif()

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

	if(TOY_ENABLE_ALPHA_API)
		if(TOY_RELEASE)
			message(WARNING "ToyBox:Are you sure? Release version shouldn't include beta stuff")
		endif()
		add_definitions(-DTOY_OPTION_ENABLE_ALPHA_API=1)
	else()
		add_definitions(-DTOY_OPTION_ENABLE_ALPHA_API=0)
	endif()

	if(TOY_ENABLE_MAY_REMOVED)
		add_definitions(-DTOY_OPTION_ENABLE_MAY_REMOVED=1)
	else()
		add_definitions(-DTOY_OPTION_ENABLE_MAY_REMOVED=0)
	endif()

	if(TOY_USE_GLEW)
		add_definitions(-DTOY_OPTION_USE_GLEW=1)
	else()
		add_definitions(-DTOY_OPTION_USE_GLEW=0)
	endif()

	list(APPEND TOY_DEFAULT_INCLUDE_DIR ${TOY_include_boost})
	list(APPEND TOY_DEFAULT_INCLUDE_DIR ${TOY_include_sfml})
	list(APPEND TOY_DEFAULT_LINK_DIR    ${TOY_library_boost})
	list(APPEND TOY_DEFAULT_LINK_DIR    ${TOY_library_sfml})

	if(WIN32)
		# 0x0A00 Windows 10
		# 0x0603 Windows 8.1
		# 0x0602 Windows 8
		# 0x0601 Windows 7
		# 0x0600 Windows Vista
		# 0x0501 Windows XP
		# 0x0500 Windows 2000
		# 0x0410 Windows 98
		# 0x0400 Windows 95
		# Boost need this to build library on Windows 2000 or later releases.
		add_definitions(-D_WIN32_WINNT=0x0501)
	endif()

	# To suppress some warning like this:
	#     MACOSX_RPATH is not specified for the following targets:
	#     This warning is for project developers. Use -Wno-dev to suppress it.
	if(APPLE)
		if (NOT CMAKE_VERSION VERSION_LESS 2.8.12)
			set(CMAKE_MACOSX_RPATH ON)
		endif()
	endif()

endmacro(toy_ProcessOptions)
