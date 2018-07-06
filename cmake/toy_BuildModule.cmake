
macro(toy_BuildModule _name)

	toy_ProcessArguments(_srcs _includeDirs _libDirs _linkLibs _outputDirs _linkFlags _cFlags _junk ${ARGN})

	if(_junk)
		message(WARNING "ToyBox:unkeyworded arguments : ${_junk}")
	endif()

	include_directories(${TOY_DEFAULT_INCLUDE_DIR})

	if(_includeDirs)
		include_directories(${_includeDirs})
	endif()

	if(_outputDirs)
		set(TOY_OUTPUT_PATH ${_outputDirs})
	else()
		set(TOY_OUTPUT_PATH ${TOY_ROOT_BINARY_DIR}/bin/toy)
	endif()

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_OUTPUT_PATH})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_OUTPUT_PATH})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TOY_OUTPUT_PATH})

	link_directories(${TOY_DEFAULT_LINK_DIR})

	if(_libDirs)
		link_directories(${_libDirs})
	endif()

	add_library(${_name} MODULE ${_srcs})

	if(_linkLibs)
		target_link_libraries(${_name} ${_linkLibs})
	endif()

	if(MSVC)
		set_target_properties(${_name} PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
		)
	else()
		if(WIN32)
			if( ${TOY_LIB_TYPE} STREQUAL STATIC)
				set_target_properties(${_name} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
			else()
				set_target_properties(${_name} PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
			endif()
		endif()
	endif()

endmacro(toy_BuildModule)
