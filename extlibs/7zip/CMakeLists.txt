
project(7zip)

set(VERSION "9.20")

if(NOT MSVC)
if( TOY_RELEASE )
	set(CMAKE_C_FLAGS "-O2")
else()
	set(CMAKE_C_FLAGS "-O2 -g")
endif()
endif()

set(SOURCE
	C/BraIA64.c
	C/Threads.c
	C/7zAlloc.c
	C/7zIn.c
	C/CpuArch.c
	C/Lzma2Enc.c
	C/MtCoder.c
	C/7zStream.c
	C/7zBuf.c
	C/Alloc.c
	C/Delta.c
	C/Xz.c
	C/Lzma86Dec.c
	C/Ppmd7.c
	C/7zBuf2.c
	C/LzFind.c
	C/Lzma86Enc.c
	C/XzCrc64.c
	C/7zCrc.c
	C/Bcj2.c
	C/LzmaDec.c
	C/Ppmd7Dec.c
	C/LzFindMt.c
	C/Ppmd7Enc.c
	C/XzDec.c
	C/7zCrcOpt.c
	C/7zDec.c
	C/7zFile.c
	C/Bra86.c
	C/Lzma2Dec.c
	C/LzmaEnc.c
	C/XzEnc.c
	C/Sha256.c
	C/XzIn.c
	C/LzmaLib.c
	C/Bra.c
)

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

include_directories( ${PROJECT_SOURCE_DIR}/C )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TOY_ROOT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${TOY_ROOT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

if(MSVC)
	add_library(7zip STATIC ${SOURCE})
else()
	add_library(7zip ${TOY_3RD_PARTY_LIB_TYPE} ${SOURCE})
endif()

if(MSVC)
	set_target_properties( 7zip PROPERTIES
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
			set_target_properties(7zip PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
		else()
			set_target_properties(7zip PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
		endif()
	endif()
endif()
