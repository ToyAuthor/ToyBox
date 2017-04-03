project(ToyRoot)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_ROOT)
endif()

toy_BuildLib(toy_root
	SOURCES     ${SOURCE}
)
