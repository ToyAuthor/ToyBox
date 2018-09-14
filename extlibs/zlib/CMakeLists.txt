# This CMakeLists.txt is not official document.

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

project(zlib C)

set(VERSION "1.2.8")

#option(ASM686 "Enable building i686 assembly implementation")
#option(AMD64 "Enable building amd64 assembly implementation")
set(ASM686 OFF)
set(AMD64 OFF)


include(CheckTypeSize)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckCSourceCompiles)
enable_testing()

check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(stdint.h    HAVE_STDINT_H)
check_include_file(stddef.h    HAVE_STDDEF_H)

#
# Check to see if we have large file support
#
set(CMAKE_REQUIRED_DEFINITIONS -D_LARGEFILE64_SOURCE=1)
# We add these other definitions here because CheckTypeSize.cmake
# in CMake 2.4.x does not automatically do so and we want
# compatibility with CMake 2.4.x.
if(HAVE_SYS_TYPES_H)
	list(APPEND CMAKE_REQUIRED_DEFINITIONS -DHAVE_SYS_TYPES_H)
endif()

if(HAVE_STDINT_H)
	list(APPEND CMAKE_REQUIRED_DEFINITIONS -DHAVE_STDINT_H)
endif()

if(HAVE_STDDEF_H)
	list(APPEND CMAKE_REQUIRED_DEFINITIONS -DHAVE_STDDEF_H)
endif()

check_type_size(off64_t OFF64_T)
if(HAVE_OFF64_T)
	add_definitions(-D_LARGEFILE64_SOURCE=1)
endif()

# Android NDK doesn't have fopen64.
if(TOY_ANDROID)
	add_definitions(-DIOAPI_NO_64)
endif()

set(CMAKE_REQUIRED_DEFINITIONS) # clear variable

#
# Check for fseeko
#
check_function_exists(fseeko HAVE_FSEEKO)
if(NOT HAVE_FSEEKO)
	add_definitions(-DNO_FSEEKO)
endif()

#
# Check for unistd.h
#
check_include_file(unistd.h Z_HAVE_UNISTD_H)

if(MSVC)
	#這個會令zlib.a變成zlibd.a
	#set(CMAKE_DEBUG_POSTFIX "d")
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
	# If we're doing an out of source build and the user has a zconf.h
	# in their source tree...
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h)
		message(STATUS "Renaming")
		message(STATUS "    ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h")
		message(STATUS "to 'zconf.h.included' because this file is included with zlib")
		message(STATUS "but CMake generates it automatically in the build directory.")
		file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h ${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.included)
	endif()
endif()

set(ZLIB_PC ${CMAKE_CURRENT_BINARY_DIR}/zlib.pc)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/zlib.pc.cmakein ${ZLIB_PC} @ONLY)
configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein ${CMAKE_CURRENT_BINARY_DIR}/zconf.h @ONLY)

# Maybe it should removed.
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})

# For minizip
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/contrib/minizip")


#============================================================================
# zlib
#============================================================================

set(ZLIB_PUBLIC_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/zconf.h
	zlib.h
)
set(ZLIB_PRIVATE_HDRS
	crc32.h
	deflate.h
	gzguts.h
	inffast.h
	inffixed.h
	inflate.h
	inftrees.h
	trees.h
	zutil.h
)
set(ZLIB_SRCS
	adler32.c
	compress.c
	crc32.c
	deflate.c
	gzclose.c
	gzlib.c
	gzread.c
	gzwrite.c
	inflate.c
	infback.c
	inftrees.c
	inffast.c
	trees.c
	uncompr.c
	zutil.c

	contrib/minizip/ioapi.c
#	contrib/minizip/iowin32.c
	contrib/minizip/mztools.c
	contrib/minizip/unzip.c
	contrib/minizip/zip.c
)

if(WIN32)
list( APPEND ZLIB_SRCS contrib/minizip/iowin32.c)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
	if(ASM686)
		set(ZLIB_ASMS contrib/asm686/match.S)
	elseif (AMD64)
		set(ZLIB_ASMS contrib/amd64/amd64-match.S)
	endif ()

	if(ZLIB_ASMS)
		add_definitions(-DASMV)
		set_source_files_properties(${ZLIB_ASMS} PROPERTIES LANGUAGE C COMPILE_FLAGS -DNO_UNDERLINE)
	endif()
endif()

if(MSVC)
	if(ASM686)
		ENABLE_LANGUAGE(ASM_MASM)
		set(ZLIB_ASMS
			contrib/masmx86/inffas32.asm
			contrib/masmx86/match686.asm
		)
	elseif (AMD64)
		ENABLE_LANGUAGE(ASM_MASM)
		set(ZLIB_ASMS
			contrib/masmx64/gvmat64.asm
			contrib/masmx64/inffasx64.asm
		)
	endif()

	if(ZLIB_ASMS)
		add_definitions(-DASMV -DASMINF)
	endif()
endif()

# parse the full version number from zlib.h and include in ZLIB_FULL_VERSION
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/zlib.h _zlib_h_contents)
string(REGEX REPLACE ".*#define[ \t]+ZLIB_VERSION[ \t]+\"([-0-9A-Za-z.]+)\".*"
    "\\1" ZLIB_FULL_VERSION ${_zlib_h_contents})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TOY_ROOT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

if(MSVC)
	add_library(zlib STATIC ${ZLIB_SRCS} ${ZLIB_ASMS} ${ZLIB_PUBLIC_HDRS} ${ZLIB_PRIVATE_HDRS})
else()
	if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
		add_library(zlib SHARED ${ZLIB_SRCS} ${ZLIB_ASMS} ${ZLIB_PUBLIC_HDRS} ${ZLIB_PRIVATE_HDRS})
		#set_target_properties(zlib PROPERTIES DEFINE_SYMBOL ZLIB_DLL)
		#set_target_properties(zlib PROPERTIES SOVERSION 1)
	else()
		add_library(zlib STATIC ${ZLIB_SRCS} ${ZLIB_ASMS} ${ZLIB_PUBLIC_HDRS} ${ZLIB_PRIVATE_HDRS})
	endif()
endif()


if(MSVC)
	set_target_properties( zlib PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
	LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
	LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY            ${TOY_ROOT_BINARY_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_ROOT_BINARY_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_ROOT_BINARY_DIR}/bin
	ARCHIVE_OUTPUT_DIRECTORY            ${CMAKE_CURRENT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${CMAKE_CURRENT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${CMAKE_CURRENT_BINARY_DIR}
	)
endif()
