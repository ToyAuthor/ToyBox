project(ToyGraph)

toy_StdReady()

file(GLOB SOURCE
	*.cpp
	*/*.cpp
)

set(LIBS toy)

if(NOT TOY_ANDROID)
if(TOY_USE_GLEW)
	include_directories(${TOY_include_glew})
	link_directories(${TOY_library_glew})
	list(APPEND LIBS ${TOY_libname_glew})
endif()
endif()

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_GRAPH)
else()
	add_definitions(-DGLEW_STATIC)
endif()

toy_BuildLib(toy_graph
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
