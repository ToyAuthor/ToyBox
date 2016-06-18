project(ToyScene)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	boost_filesystem
	boost_system
)

toy_BuildLib(toy_scene
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
