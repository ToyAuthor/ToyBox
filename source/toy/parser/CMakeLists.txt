project(ToyParser)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	boost_filesystem
	boost_system
)

toy_BuildLib(toy_parser
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
