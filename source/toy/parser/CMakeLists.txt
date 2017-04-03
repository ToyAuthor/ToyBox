project(ToyParser)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	boost_filesystem
	boost_system
)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_PARSER)
endif()

toy_BuildLib(toy_parser
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
