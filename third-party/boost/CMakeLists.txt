project(boost)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

set( BOOST_ROOT_SOURCE_DIR     ${PROJECT_SOURCE_DIR} )
set( BOOST_ROOT_BINARY_DIR     ${PROJECT_BINARY_DIR} )
set( BOOST_LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

set(BOOST_INCLUDE_DIR ${TOY_include_boost} )

#option(BOOST_BUILD_SHARED_LIBS    "Make shared library"      OFF)

if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
	set(BOOST_BUILD_SHARED_LIBS ON)
else()
	set(BOOST_BUILD_SHARED_LIBS OFF)
endif()


link_directories(${BOOST_LIBRARY_OUTPUT_PATH})

if(BOOST_BUILD_SHARED_LIBS)
	set(BOOST_LIBRARY_TYPE SHARED)
else()
	set(BOOST_LIBRARY_TYPE STATIC)
endif()

# Disable auto link.
add_definitions(-DBOOST_ALL_NO_LIB)

add_subdirectory(libs)
