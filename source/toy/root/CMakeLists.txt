project(ToyRoot)

toy_StdReady()


set(SOURCE
	Root.cpp
)


toy_BuildLib(toy_root
	SOURCES     ${SOURCE}
)
