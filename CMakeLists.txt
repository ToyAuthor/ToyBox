project(ToyBox)
cmake_minimum_required(VERSION 2.8)


set(TOY_ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(TOY_ROOT_BINARY_DIR ${PROJECT_BINARY_DIR})

if(CMAKE_BUILD_TYPE MATCHES Release)
	set(TOY_RELEASE ON)
else()
	set(TOY_RELEASE OFF)
endif()

include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyTools.cmake" REQUIRED)

option(TOY_ENABLE_SHARED_LIBS   "Make shared library"       OFF)

set(TOY_RESOURCE_PATH "${TOY_ROOT_SOURCE_DIR}/resource")


set(TOY_DEFAULT_INCLUDE_DIR ${TOY_ROOT_SOURCE_DIR}/include ${TOY_ROOT_SOURCE_DIR}/source)

set(TOY_DEFAULT_LINK_DIR ${TOY_ROOT_BINARY_DIR}/lib )

toy_IncludeTools()

add_subdirectory(third-party)
add_subdirectory(source/toy)
add_subdirectory(examples)
