project(ToyRoot)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

toy_BuildLib(toy_root
	SOURCES     ${SOURCE}
)
