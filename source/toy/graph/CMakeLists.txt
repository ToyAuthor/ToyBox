project(ToyGraph)

toy_StdReady()

file(GLOB SOURCE
	*.cpp
	*/*.cpp
)

set(LIBS toy)

if(NOT TOY_ANDROID)
	list(APPEND LIBS ${TOY_libname_glew})
endif()

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_GRAPH)
else()
	add_definitions(-DGLEW_STATIC)
endif()

toy_BuildLib(toy_graph
	INCLUDEDIRS ${TOY_include_glew}
	LIBDIRS     ${TOY_library_glew}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
