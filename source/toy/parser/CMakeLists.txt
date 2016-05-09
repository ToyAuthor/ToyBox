project(ToyParser)

toy_StdReady()


set(SOURCE
	Parser.cpp
	Translator.cpp
	StringCutter.cpp
	StringCutterConfig.cpp
)

set(LIBS toy
	boost_filesystem
	boost_system
)

toy_BuildLib(toy_parser
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
