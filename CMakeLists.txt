
project(ToyBox)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
	#set(CMAKE_BUILD_TYPE "Release")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

#-------------------------------------------------------------------------------

option(TOY_ENABLE_SHARED_LIBS   "Make shared library"       OFF)

set(TOY_ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(TOY_ROOT_BINARY_DIR ${PROJECT_BINARY_DIR})

set(TOY_RESOURCE_PATH       ${TOY_ROOT_SOURCE_DIR}/resource)
set(TOY_DEFAULT_INCLUDE_DIR ${TOY_ROOT_SOURCE_DIR}/include ${TOY_ROOT_SOURCE_DIR}/source)
set(TOY_DEFAULT_LINK_DIR    ${TOY_ROOT_BINARY_DIR}/lib)

include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyTools.cmake" REQUIRED)
toy_IncludeTools()

#-------------------------------------------------------------------------------

add_subdirectory(third-party)
add_subdirectory(source)
add_subdirectory(source/toy)
add_subdirectory(examples)

if(NOT TOY_ANDROID)
	add_subdirectory(tools)

	if(TOY_ENABLE_SHARED_LIBS)
		add_subdirectory(modules)
	endif()
endif()
