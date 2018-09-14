# This CMakeLists.txt is not official document.

project(ToyLz4)

toy_StdReady()

if(TOY_ENABLE_3RD_PARTY_SHARED_LIB AND WIN32)
	add_definitions(-DLZ4_DLL_EXPORT=1)
endif()

if(UNIX)
	if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
		#add_definitions()
	else()
		add_definitions(-fPIC -fvisibility=hidden)
	endif()
endif()

file(GLOB SOURCE *.c)

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TOY_ROOT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${TOY_ROOT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_library(lz4 ${TOY_3RD_PARTY_LIB_TYPE} ${SOURCE})

if(MSVC)

	set_target_properties( lz4 PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY            "${TOY_ROOT_BINARY_DIR}/bin"
			LIBRARY_OUTPUT_DIRECTORY_DEBUG      "${TOY_ROOT_BINARY_DIR}/bin"
			LIBRARY_OUTPUT_DIRECTORY_RELEASE    "${TOY_ROOT_BINARY_DIR}/bin"
			RUNTIME_OUTPUT_DIRECTORY            "${TOY_ROOT_BINARY_DIR}/bin"
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      "${TOY_ROOT_BINARY_DIR}/bin"
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    "${TOY_ROOT_BINARY_DIR}/bin"
			ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
			)
else()
	if(WIN32)
		if( ${TOY_3RD_PARTY_LIB_TYPE} STREQUAL STATIC)
			set_target_properties(lz4 PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
		else()
			set_target_properties(lz4 PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
		endif()
	endif()
endif()
