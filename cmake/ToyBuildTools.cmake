
if(TOY_ANDROID)
	include("${PROJECT_SOURCE_DIR}/cmake/android/create_apk.cmake" REQUIRED)
endif()

macro(toy_StdReady)
	if(NOT MSVC)
		if( TOY_RELEASE )
			add_definitions(-O2 -s -Werror -Wall -Wextra)
		else()
			add_definitions(-O2 -g -Werror -Wall -Wextra)
		endif()

		if(WIN32)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
		else()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		endif()

		if(APPLE)
			add_definitions(-Qunused-arguments)
		elseif(UNIX)
			include_directories(/usr/include)

			if(CMAKE_SIZEOF_VOID_P EQUAL 8)
				link_directories(/usr/lib/x86_64-linux-gnu)
			else()
				link_directories(/usr/lib)
			endif()
		endif()
	endif()
endmacro(toy_StdReady)

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

macro(toy_BuildLib _name)

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
		set(TOY_OUTPUT_PATH ${TOY_ROOT_BINARY_DIR}/lib)
	endif()

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_OUTPUT_PATH})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TOY_OUTPUT_PATH})

	link_directories(${TOY_DEFAULT_LINK_DIR})

	if(_libDirs)
		link_directories(${_libDirs})
	endif()

	add_library(${_name} ${TOY_LIB_TYPE} ${_srcs})

	if(_linkLibs)
		target_link_libraries(${_name} ${_linkLibs})
	endif()

	if(MSVC)
		set_target_properties(${_name} PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
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

endmacro(toy_BuildLib)

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
