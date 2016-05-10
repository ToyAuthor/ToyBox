# This CMakeLists.txt is not official document.

project(ToyLua)

set(VERSION "5.3.0")

toy_StdReadyC()

if(UNIX)
	# I'm not sure it's good or not.
	add_definitions(-fPIC -DLUA_USE_POSIX)
endif()


set(SOURCE
	lapi.c
	lauxlib.c
	lbaselib.c
	lbitlib.c
	lcode.c
	lcorolib.c
	lctype.c
	ldblib.c
	ldebug.c
	ldo.c
	ldump.c
	lfunc.c
	lgc.c
	linit.c
	liolib.c
	llex.c
	lmathlib.c
	lmem.c
	loadlib.c
	lobject.c
	lopcodes.c
	loslib.c
	lparser.c
	lstate.c
	lstring.c
	lstrlib.c
	ltable.c
	ltablib.c
	ltm.c
#	lua.c   We don't need it
#	luac.c  We don't need it
	lundump.c
	lutf8lib.c
	lvm.c
	lzio.c
	)


set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
add_library(lua ${TOY_3RD_PARTY_LIB_TYPE} ${SOURCE})

if(TOY_ENABLE_3RD_PARTY_SHARED_LIB AND MSVC)
	# It need CMake version higher than v2.8
	target_compile_definitions(lua PRIVATE "LUA_BUILD_AS_DLL")
endif()

if(MSVC)
	set_target_properties( lua PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
	RUNTIME_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
	)
endif()
