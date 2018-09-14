
set(PROJECT_NAME boost_regex)

project(${PROJECT_NAME})

include_directories(${BOOST_INCLUDE_DIR})

if(BOOST_BUILD_SHARED_LIBS)
	add_definitions(-DBOOST_REGEX_DYN_LINK=1)
endif()

set(SOURCE
	src/c_regex_traits.cpp
	src/cpp_regex_traits.cpp
	src/cregex.cpp
	src/fileiter.cpp
	src/icu.cpp
	src/instances.cpp
	src/posix_api.cpp
	src/regex.cpp
	src/regex_debug.cpp
	src/regex_raw_buffer.cpp
	src/regex_traits_defaults.cpp
	src/static_mutex.cpp
	src/w32_regex_traits.cpp
	src/wc_regex_traits.cpp
	src/wide_posix_api.cpp
	src/winstances.cpp
	src/usinstances.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BOOST_LIBRARY_OUTPUT_PATH})

add_library(${PROJECT_NAME} ${BOOST_LIBRARY_TYPE} ${SOURCE})

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
		LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
		LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
		RUNTIME_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
		RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
		RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
		ARCHIVE_OUTPUT_DIRECTORY            ${BOOST_LIBRARY_OUTPUT_PATH}
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${BOOST_LIBRARY_OUTPUT_PATH}
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${BOOST_LIBRARY_OUTPUT_PATH}
	)
else()
	if(WIN32)
		if( ${BOOST_LIBRARY_TYPE} STREQUAL STATIC)
			set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
		else()
			set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
		endif()
	endif()
endif()
