project(ToyScene)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	toy_graph
)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_SCENE)
endif()

toy_BuildLib(toy_scene
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
