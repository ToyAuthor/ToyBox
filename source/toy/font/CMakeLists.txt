project(ToyFont)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	${TOY_libname_freetype}
)

set(INC_DIR
	${TOY_include_freetype}
)

set(LIB_DIR
	${TOY_library_freetype}
)


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_FONT)
endif()

toy_BuildLib(toy_font
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
