# This CMakeLists.txt is not official document.

project(ToySQLite)

set(VERSION "3.28.0")

if(UNIX)
	add_definitions(-fPIC)
endif()

if(NOT MSVC)
if( TOY_RELEASE )
	set(CMAKE_C_FLAGS "-O2")
else()
	set(CMAKE_C_FLAGS "-O2 -g")
endif()
endif()

file(GLOB SOURCE *.c)

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

# Too old
# set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_library(sqlite3 STATIC ${SOURCE})

if(UNIX)
	# Link them if you want to create C extension module.
	target_link_libraries(sqlite3 dl)
endif()

if(MSVC)
	set_target_properties( sqlite3 PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
			LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
			LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
			RUNTIME_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
			ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
			)
else()
	if(WIN32)
		if( ${TOY_3RD_PARTY_LIB_TYPE} STREQUAL STATIC)
			set_target_properties(sqlite3 PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
		else()
			set_target_properties(sqlite3 PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
		endif()
	endif()
endif()
