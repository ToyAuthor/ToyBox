
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/android/EnableAndroidMode.cmake" REQUIRED)
toy_EnableAndroidMode()

project(ToyBox)
cmake_minimum_required(VERSION 2.8)


set(TOY_ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(TOY_ROOT_BINARY_DIR ${PROJECT_BINARY_DIR})


if(NOT CMAKE_BUILD_TYPE)
	#set(CMAKE_BUILD_TYPE "Release")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
	set(TOY_RELEASE ON)
else()
	set(TOY_RELEASE OFF)
endif()


option(TOY_ENABLE_SHARED_LIBS   "Make shared library"       OFF)

set(TOY_RESOURCE_PATH       ${TOY_ROOT_SOURCE_DIR}/resource)
set(TOY_DEFAULT_INCLUDE_DIR ${TOY_ROOT_SOURCE_DIR}/include ${TOY_ROOT_SOURCE_DIR}/source)
set(TOY_DEFAULT_LINK_DIR    ${TOY_ROOT_BINARY_DIR}/lib)

# To suppress some warning like this:
#     MACOSX_RPATH is not specified for the following targets:
#     This warning is for project developers.  Use -Wno-dev to suppress it.
if(APPLE)
	if (NOT CMAKE_VERSION VERSION_LESS 2.8.12)
		set(CMAKE_MACOSX_RPATH ON)
	endif()
endif()

include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyTools.cmake" REQUIRED)
toy_IncludeTools()

add_subdirectory(third-party)
add_subdirectory(source)
add_subdirectory(source/toy)
add_subdirectory(examples)
