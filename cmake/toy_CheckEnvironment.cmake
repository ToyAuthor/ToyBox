
macro(toy_CheckEnvironment)

	if(NOT (MINGW OR MSVC OR UNIX OR TOY_ANDROID))
		message(WARNING "ToyBox:Sorry, this compiler haven't been tested.")
	endif()

	if(CMAKE_BUILD_TYPE MATCHES Release)
		if(TOY_ENABLE_ALPHA_API)
			message(WARNING "ToyBox:Release version should turn off TOY_ENABLE_ALPHA_API.")
		endif()
	endif()

endmacro(toy_CheckEnvironment)
