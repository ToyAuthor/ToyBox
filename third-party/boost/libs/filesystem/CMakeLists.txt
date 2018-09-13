
set(PROJECT_NAME boost_filesystem)

project(${PROJECT_NAME})

include_directories(${BOOST_INCLUDE_DIR})

if(BOOST_BUILD_SHARED_LIBS)
	add_definitions(-DBOOST_FILESYSTEM_DYN_LINK=1)
else()
	add_definitions(-DBOOST_FILESYSTEM_STATIC_LINK=1)
endif()


set(SOURCE
	src/codecvt_error_category.cpp
	src/operations.cpp
	src/path.cpp
	src/path_traits.cpp
	src/portability.cpp
	src/unique_path.cpp
	src/utf8_codecvt_facet.cpp
	src/windows_file_codecvt.cpp
)

set(LIB
	boost_system
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BOOST_LIBRARY_OUTPUT_PATH})

add_library(${PROJECT_NAME} ${BOOST_LIBRARY_TYPE} ${SOURCE})

target_link_libraries(${PROJECT_NAME} ${LIB})

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
