
project(ToyBox)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
#	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
	set(CMAKE_BUILD_TYPE "Debug"   CACHE STRING "Choose the type of build" FORCE)
endif()

#-------------------------------------------------------------------------------

option(TOY_ENABLE_SHARED_LIBS   "Make shared library"       ON)

set(TOY_ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(TOY_ROOT_BINARY_DIR ${PROJECT_BINARY_DIR})

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
