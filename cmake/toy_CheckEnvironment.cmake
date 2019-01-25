
macro(toy_CheckEnvironment)

	if(NOT (MINGW OR MSVC OR UNIX OR TOY_ANDROID))
		message(WARNING "ToyBox:Sorry, this compiler haven't been tested.")
	endif()

	if(CMAKE_BUILD_TYPE MATCHES Release)
		if(TOY_ENABLE_BETA_API)
			message(WARNING "ToyBox:Release version shouldn't include beta stuff.")
		endif()
	endif()

endmacro(toy_CheckEnvironment)
