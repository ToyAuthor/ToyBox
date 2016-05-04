
macro(toy_CheckEnvironment)

	if(NOT (MINGW OR MSVC OR UNIX))
		message("ToyBox:Sorry, this compiler haven't been tested.")
	endif()

endmacro(toy_CheckEnvironment)
