project(ToyTime)

toy_StdReady()

file(GLOB SOURCE *.cpp)

set(LIBS toy)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_TIME)
endif()

toy_BuildLib(toy_time
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
