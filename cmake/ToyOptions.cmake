
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

endmacro(toy_ProcessOptions)
