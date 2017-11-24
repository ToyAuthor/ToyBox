project(ToyFile)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	boost_filesystem
	boost_system
	${TOY_libname_zlib}
	${TOY_libname_7zip}
	lz4
)

set(INC_DIR
	${TOY_include_zlib}
	${TOY_include_7zip}
)

set(LIB_DIR
	${TOY_library_zlib}
	${TOY_library_7zip}
)


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_FILE)
endif()

if(TOY_ENABLE_SHARED_LIBS AND WIN32)
	add_definitions(-DLZ4_DLL_IMPORT=1)
endif()

include_directories(${TOY_ROOT_SOURCE_DIR}/third-party/lz4)
link_directories(${TOY_ROOT_BINARY_DIR}/third-party/lz4)


toy_BuildLib(toy_file
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
