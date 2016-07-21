
project(p7zip)

add_definitions(-O2 -g)
include_directories(/usr/include)
link_directories(/usr/lib)


add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DNDEBUG -D_REENTRANT -DENV_UNIX -DBREAK_HANDLER -DUNICODE -D_UNICODE)


if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
	add_definitions(-fPIC)
endif()


set(SOURCE
	C/Aes.c
	C/7zStream.c
	C/Alloc.c
	C/Bra.c
	C/Bra86.c
	C/BraIA64.c
	C/BwtSort.c
	C/Delta.c
	C/HuffEnc.c
	C/LzFind.c
	C/LzFindMt.c
	C/Lzma2Dec.c
	C/Lzma2Enc.c
	C/LzmaDec.c
	C/LzmaEnc.c
	C/MtCoder.c
	C/Ppmd7.c
	C/Ppmd7Dec.c
	C/Ppmd7Enc.c
	C/Ppmd8.c
	C/Ppmd8Dec.c
	C/Ppmd8Enc.c
	C/Sha256.c
	C/Sort.c
	C/Threads.c
	C/Xz.c
	C/XzCrc64.c
	C/XzDec.c
	C/XzEnc.c
	C/XzIn.c

	C/7zCrc.c
	C/7zCrcOpt.c
	C/7zFile.c
	C/7zIn.c
	C/7zBuf.c
	C/7zDec.c
	C/Bcj2.c
	)

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

include_directories( ${PROJECT_SOURCE_DIR}/C )

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_library(p7zip ${TOY_3RD_PARTY_LIB_TYPE} ${SOURCE})
