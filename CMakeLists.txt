
project(ToyBox)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
#	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
	set(CMAKE_BUILD_TYPE "Debug"   CACHE STRING "Choose the type of build" FORCE)
endif()

set(TOY_ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(TOY_ROOT_BINARY_DIR ${PROJECT_BINARY_DIR})

include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_IncludeTools.cmake" REQUIRED)
toy_IncludeTools()

add_subdirectory(extlibs)
add_subdirectory(src)
add_subdirectory(src/toy)
add_subdirectory(examples)
add_subdirectory(test)
add_subdirectory(tools)

if(TOY_ENABLE_SHARED_LIBS)
	add_subdirectory(modules)
endif()
