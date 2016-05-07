# This CMakeLists.txt is not official document.


set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")

project(libpng C)

set(VERSION "1.6.12")

enable_testing()


set(PNGLIB_NAME libpng${PNGLIB_MAJOR}${PNGLIB_MINOR})


include_directories(${ZLIB_INCLUDE_DIR})

if(NOT WIN32)
	find_library(M_LIBRARY
		NAMES m
		PATHS /usr/lib /usr/local/lib
		)
	if(NOT M_LIBRARY)
		message(STATUS "math library 'libm' not found - floating point support disabled")
	endif()
else()
	# not needed on windows
	set(M_LIBRARY "")
endif()


# COMMAND LINE OPTIONS
#if(DEFINED PNG_SHARED)
#	#option(PNG_SHARED "Build shared lib" ${PNG_SHARED})
#	set(PNG_SHARED ${PNG_SHARED})
#else()
#	#option(PNG_SHARED "Build shared lib" OFF)
#	set(PNG_SHARED OFF)
#endif()
#if(DEFINED PNG_STATIC)
#	#option(PNG_STATIC "Build static lib" ${PNG_STATIC})
#	set(PNG_STATIC ${PNG_STATIC})
#else()
#	#option(PNG_STATIC "Build static lib" ON)
#	set(PNG_STATIC ON)
#endif()


if(MSVC)
	set(PNG_SHARED OFF)
	set(PNG_STATIC ON)
else()
	if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
		set(PNG_SHARED ON)
		set(PNG_STATIC OFF)
	else()
		set(PNG_SHARED OFF)
		set(PNG_STATIC ON)
	endif()
endif()


#option(PNG_TESTS  "Build libpng tests" YES)
set(PNG_TESTS NO)

# Many more configuration options could be added here
#option(PNG_DEBUG         "Build with debug output" NO)
#option(PNGARG            "Disable ANSI-C prototypes" NO)
set(PNG_DEBUG NO)
set(PNGARG    NO)

set(PNG_LIB_NAME png)

# to distinguish between debug and release lib
#set(CMAKE_DEBUG_POSTFIX "d")

# Use the prebuilt pnglibconf.h file from the scripts folder
# TODO: fix this by building with awk; without this no cmake build can be
# configured directly (to do so indirectly use your local awk to build a
# pnglibconf.h in the build directory.)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/pnglibconf.h.prebuilt
               ${CMAKE_CURRENT_BINARY_DIR}/pnglibconf.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# OUR SOURCES
set(libpng_public_hdrs
	png.h
	pngconf.h
	${CMAKE_CURRENT_BINARY_DIR}/pnglibconf.h
)
set(libpng_sources
	${libpng_public_hdrs}
	pngdebug.h
	pnginfo.h
	pngpriv.h
	pngstruct.h
	png.c
	pngerror.c
	pngget.c
	pngmem.c
	pngpread.c
	pngread.c
	pngrio.c
	pngrtran.c
	pngrutil.c
	pngset.c
	pngtrans.c
	pngwio.c
	pngwrite.c
	pngwtran.c
	pngwutil.c
)
set(pngtest_sources
	pngtest.c
)
set(pngvalid_sources
	contrib/libtests/pngvalid.c
)
set(pngstest_sources
	contrib/libtests/pngstest.c
)
# SOME NEEDED DEFINITIONS

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif(MSVC)

if(PNG_DEBUG)
	add_definitions(-DPNG_DEBUG)
endif()

# NOW BUILD OUR TARGET
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${ZLIB_INCLUDE_DIR})

unset(PNG_LIB_TARGETS)

if(PNG_SHARED)
	add_library(${PNG_LIB_NAME} SHARED ${libpng_sources})
	set(PNG_LIB_TARGETS ${PNG_LIB_NAME})
	if(MSVC)
		# msvc does not append 'lib' - do it here to have consistent name
		set_target_properties(${PNG_LIB_NAME} PROPERTIES PREFIX "lib")
		set_target_properties(${PNG_LIB_NAME} PROPERTIES IMPORT_PREFIX "lib")
	endif()
	target_link_libraries(${PNG_LIB_NAME} ${ZLIB_LIBRARY} ${M_LIBRARY})
endif()

if(PNG_STATIC)
	# does not work without changing name
	#set(PNG_LIB_NAME_STATIC ${PNG_LIB_NAME}_static)
	set(PNG_LIB_NAME_STATIC ${PNG_LIB_NAME})
	add_library(${PNG_LIB_NAME_STATIC} STATIC ${libpng_sources})
	list(APPEND PNG_LIB_TARGETS ${PNG_LIB_NAME_STATIC})
	if(MSVC)
		# msvc does not append 'lib' - do it here to have consistent name
		#set_target_properties(${PNG_LIB_NAME_STATIC} PROPERTIES PREFIX "lib")
	endif()
	target_link_libraries(${PNG_LIB_NAME_STATIC} ${ZLIB_LIBRARY} ${M_LIBRARY})
endif()

if(NOT PNG_LIB_TARGETS)
	message(SEND_ERROR
		"No library variant selected to build. "
		"Please enable at least one of the following options: PNG_STATIC, PNG_SHARED")
endif()

if(PNG_SHARED AND WIN32)
	# Just like TOY_EXPORT. I guess.
	set_target_properties(${PNG_LIB_NAME} PROPERTIES DEFINE_SYMBOL PNG_BUILD_DLL)
endif()

if(PNG_TESTS AND PNG_SHARED)
	# does not work with msvc due to png_lib_ver issue
	add_executable(pngtest ${pngtest_sources})
	target_link_libraries(pngtest ${PNG_LIB_NAME})
	add_test(pngtest ./pngtest ${CMAKE_CURRENT_SOURCE_DIR}/pngtest.png)
	#
	add_executable(pngvalid ${pngvalid_sources})
	target_link_libraries(pngvalid ${PNG_LIB_NAME})
	add_test(pngvalid ./pngvalid)
	add_executable(pngstest ${pngstest_sources})
	target_link_libraries(pngstest ${PNG_LIB_NAME})
	add_test(pngstest ./pngstest
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g01.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g02.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g04.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn2c08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn2c16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p01.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p02.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p04.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn4a08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn4a16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn6a08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn6a16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn0g01.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn0g02.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn0g04.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn2c16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn3p08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbgn2c16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbgn3p08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbrn2c08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbwn0g16.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbwn3p08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbyn3p08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp0n0g08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp0n2c08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp0n3p08.png
		${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp1n3p08.png
	)
endif()

# Ensure the CMAKE_LIBRARY_OUTPUT_DIRECTORY is set
IF(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")
ENDIF(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)

# Set a variable with CMake code which:
# Creates a symlink from src to dest (if possible) or alternatively
# copies if different.
macro(CREATE_SYMLINK SRC_FILE DEST_FILE)
	FILE(REMOVE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${DEST_FILE})
	if(WIN32 AND NOT CYGWIN AND NOT MSYS)
		ADD_CUSTOM_COMMAND(
			OUTPUT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${DEST_FILE}   ${CMAKE_CURRENT_BINARY_DIR}/${DEST_FILE}
			COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${SRC_FILE}" ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${DEST_FILE}
			COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${SRC_FILE}" ${CMAKE_CURRENT_BINARY_DIR}/${DEST_FILE}
			DEPENDS ${PNG_LIB_TARGETS}
			)
		ADD_CUSTOM_TARGET(${DEST_FILE}_COPY ALL DEPENDS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${DEST_FILE})
	else(WIN32 AND NOT CYGWIN AND NOT MSYS)
		get_filename_component(LINK_TARGET "${SRC_FILE}" NAME)
		execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${LINK_TARGET}" ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${DEST_FILE} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
		execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${LINK_TARGET}" ${DEST_FILE} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
	endif(WIN32 AND NOT CYGWIN AND NOT MSYS)
endmacro()

# libpng is a library so default to 'lib'
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
	set(CMAKE_INSTALL_LIBDIR lib)
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)

# CREATE PKGCONFIG FILES
# we use the same files like ./configure, so we have to set its vars
# Only do this on Windows for Cygwin - the files don't make much sense outside
# a UNIX look alike
if(NOT WIN32 OR CYGWIN OR MINGW)
	set(prefix      ${CMAKE_INSTALL_PREFIX})
	set(exec_prefix ${CMAKE_INSTALL_PREFIX})
	set(libdir      ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
	set(includedir  ${CMAKE_INSTALL_PREFIX}/include)
	set(LIBS        "-lz -lm")
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libpng.pc.in
		${CMAKE_CURRENT_BINARY_DIR}/${PNGLIB_NAME}.pc @ONLY)
	#CREATE_SYMLINK(${PNGLIB_NAME}.pc libpng.pc)

	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libpng-config.in
		${CMAKE_CURRENT_BINARY_DIR}/${PNGLIB_NAME}-config @ONLY)
	#CREATE_SYMLINK(${PNGLIB_NAME}-config libpng-config)
endif(NOT WIN32 OR CYGWIN OR MINGW)

if(MSVC)
	set_target_properties( ${PNG_LIB_NAME} PROPERTIES
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
