project(MemoryTest01)

toy_StdReady()

set(LIBS
	toy
	toy_memory
)

set(SOURCE
	main.cpp
)

toy_BuildExe(MemoryTest01
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
