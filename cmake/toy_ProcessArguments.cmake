
macro(toy_ProcessArguments _sourcesArgs _includeDirsArgs _libDirsArgs _linkLibsArgs _outputDirsArgs _linkFlagsArgs _cFlagsArgs _otherArgs)
	set(${_sourcesArgs})
	set(${_includeDirsArgs})
	set(${_libDirsArgs})
	set(${_linkLibsArgs})
	set(${_outputDirsArgs})
	set(${_linkFlagsArgs})
	set(${_cFlagsArgs})
	set(${_otherArgs})
	set(_currentDest ${_otherArgs})

	foreach(_arg ${ARGN})
		if    (_arg STREQUAL "SOURCES")
			set(_currentDest ${_sourcesArgs})
		elseif(_arg STREQUAL "INCLUDEDIRS")
			set(_currentDest ${_includeDirsArgs})
		elseif(_arg STREQUAL "LIBDIRS")
			set(_currentDest ${_libDirsArgs})
		elseif(_arg STREQUAL "LINKLIBS")
			set(_currentDest ${_linkLibsArgs})
		elseif(_arg STREQUAL "OUTPUTDIRS")
			set(_currentDest ${_outputDirsArgs})
		elseif(_arg STREQUAL "LINKFLAGS")
			set(_currentDest ${_linkFlagsArgs})
		elseif(_arg STREQUAL "CFLAGS")
			set(_currentDest ${_cFlagsArgs})
		else()
			list(APPEND ${_currentDest} ${_arg})
		endif()
	endforeach()
endmacro(toy_ProcessArguments)
