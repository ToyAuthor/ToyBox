
macro(toy_BuildExe _name)

	toy_ProcessArguments(_srcs _includeDirs _libDirs _linkLibs _outputDirs _linkFlags _cFlags _junk ${ARGN})

	if(_junk)
		message(WARNING "ToyBox:unkeyworded arguments : ${_junk}")
	endif()

	include_directories(${TOY_DEFAULT_INCLUDE_DIR})
	link_directories(${TOY_DEFAULT_LINK_DIR})

	if(_includeDirs)
		include_directories(${_includeDirs})
	endif()

	if(_libDirs)
		link_directories(${_libDirs})
	endif()

	if(_outputDirs)
		set(TOY_OUTPUT_PATH ${_outputDirs})
	else()
		set(TOY_OUTPUT_PATH ${TOY_ROOT_BINARY_DIR}/bin)
	endif()

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_OUTPUT_PATH})

	if(TOY_ANDROID)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/apk/libs/${ANDROID_NDK_ABI_NAME})
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/apk/libs/${ANDROID_NDK_ABI_NAME})
		add_library(${_name} SHARED ${_srcs})
	else()
		add_executable(${_name} ${_srcs})
	endif()

	if(_linkLibs)
		target_link_libraries(${_name} ${_linkLibs})
	endif()

	if(TOY_ANDROID)
		set_target_properties(${_name} PROPERTIES COMPILE_DEFINITIONS "ANDROID")
		create_apk(
			${_name}
			"toy.example.${_name}"
			"${TOY_ROOT_BINARY_DIR}/apk"
			"${TOY_ROOT_SOURCE_DIR}/libs"
			"${TOY_ROOT_SOURCE_DIR}/android"
			"${TOY_ROOT_SOURCE_DIR}/resource/android"
		)
	elseif(MSVC)
		set_target_properties(${_name} PROPERTIES
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

endmacro(toy_BuildExe)
