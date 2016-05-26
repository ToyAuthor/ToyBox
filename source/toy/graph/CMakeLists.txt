project(ToyGraph)

toy_StdReady()

add_definitions(-DGLEW_STATIC)

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	${TOY_libname_sfml_system}
	${TOY_libname_sfml_window}
	${TOY_libname_glew}
)

toy_BuildLib(toy_graph
	INCLUDEDIRS ${TOY_include_glew}
	LIBDIRS     ${TOY_library_glew}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
