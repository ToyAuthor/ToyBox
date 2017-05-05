# This CMakeLists.txt is not official document.


project(libglew)

set(VERSION "1.11.0")

include_directories( ${PROJECT_SOURCE_DIR}/include )

set( LIBRARY_OUTPUT_PATH	${PROJECT_BINARY_DIR} )
set( EXECUTABLE_OUTPUT_PATH	${PROJECT_BINARY_DIR} )

# There is no glu on android. By the way, android doesn't need glew anyway.
add_definitions(-DGLEW_NO_GLU)

if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
	if(WIN32)
		add_definitions(-DGLEW_BUILD)
	endif()
else()
	add_definitions(-DGLEW_STATIC)
endif()

if(WIN32)
	set( LIBS opengl32 )
	add_definitions( -DWIN32_MEAN_AND_LEAN -DVC_EXTRALEAN -D_CRT_SECURE_NO_WARNINGS )
elseif(APPLE)
	find_library(TOY_FW_OpenGL OpenGL)
	find_library(TOY_FW_AGL AGL)
	list(APPEND LIBS ${TOY_FW_OpenGL} ${TOY_FW_AGL})
elseif(UNIX)
	set( LIBS GL )
	list( APPEND LIBS X11 dl Xext )
endif()


add_library( glew ${TOY_3RD_PARTY_LIB_TYPE} ${PROJECT_SOURCE_DIR}/src/glew.c )


target_link_libraries( glew ${LIBS} )

if(MSVC)
	set_target_properties( glew PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY            ${CMAKE_CURRENT_BINARY_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${CMAKE_CURRENT_BINARY_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${CMAKE_CURRENT_BINARY_DIR}
	RUNTIME_OUTPUT_DIRECTORY            ${CMAKE_CURRENT_BINARY_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${CMAKE_CURRENT_BINARY_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${CMAKE_CURRENT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY            ${CMAKE_CURRENT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${CMAKE_CURRENT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${CMAKE_CURRENT_BINARY_DIR}
	)
endif()
