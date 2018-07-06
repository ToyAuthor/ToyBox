
macro(toy_CheckEnvironment)

	if(NOT (MINGW OR MSVC OR UNIX OR TOY_ANDROID))
		message(WARNING "ToyBox:Sorry, this compiler haven't been tested.")
	endif()

	if(TOY_ENABLE_EASY_BUILD)
		if(CMAKE_BUILD_TYPE MATCHES Release)
			message(FATAL_ERROR "ToyBox:Release version not support this option")
		else()
			if(APPLE)
				message(FATAL_ERROR "ToyBox:The option TOY_ENABLE_EASY_BUILD only supported on Linux and Windows")
			elseif(NOT (WIN32 OR UNIX))
				message(FATAL_ERROR "ToyBox:The option TOY_ENABLE_EASY_BUILD only supported on Linux and Windows")
			endif()
		endif()
	endif()

endmacro(toy_CheckEnvironment)
