project(ToyMemory)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_MEMORY)
endif()

toy_BuildLib(toy_memory
	SOURCES     ${SOURCE}
	LINKLIBS    toy
)
