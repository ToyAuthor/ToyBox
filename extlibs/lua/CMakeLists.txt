# This CMakeLists.txt is not official document.

project(ToyLua)

set(VERSION "5.3.0")

toy_StdReady()

if(TOY_ENABLE_3RD_PARTY_SHARED_LIB AND WIN32)
	add_definitions(-DLUA_BUILD_AS_DLL)
endif()

if(UNIX)
	if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
		#add_definitions(-DLUA_USE_LINUX)
		add_definitions(-DLUA_USE_POSIX -DLUA_USE_DLOPEN)
	else()
		add_definitions(-fPIC -DLUA_USE_POSIX)
	endif()
endif()

file(GLOB SOURCE *.c)

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

# Too old
# set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_library(lua ${TOY_3RD_PARTY_LIB_TYPE} ${SOURCE})

if(UNIX AND TOY_ENABLE_3RD_PARTY_SHARED_LIB)
	# Link them if you want to create C extension module.
	target_link_libraries(lua dl m)
endif()

if(MSVC)

	if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
		# It need CMake version newer than v2.8
		target_compile_definitions(lua PRIVATE "LUA_BUILD_AS_DLL")
	endif()

	set_target_properties( lua PROPERTIES
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
			set_target_properties(lua PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
		else()
			set_target_properties(lua PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
		endif()
	endif()
endif()
