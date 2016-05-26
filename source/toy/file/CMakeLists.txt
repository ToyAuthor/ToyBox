project(ToyFile)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	boost_filesystem
	boost_system
	${TOY_libname_zlib}
	${TOY_libname_libpng}
	${TOY_libname_7zip}
)

set(INC_DIR
	${TOY_include_libpng}
	${TOY_include_zlib}
	${TOY_include_7zip}
)

set(LIB_DIR
	${TOY_library_libpng}
	${TOY_library_zlib}
	${TOY_library_7zip}
)


toy_BuildLib(toy_file
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
