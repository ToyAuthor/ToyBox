
project(ToyBox)
cmake_minimum_required(VERSION 2.8)

set(TOY_ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(TOY_ROOT_BINARY_DIR ${PROJECT_BINARY_DIR})

include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyTools.cmake" REQUIRED)
toy_IncludeTools()

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
