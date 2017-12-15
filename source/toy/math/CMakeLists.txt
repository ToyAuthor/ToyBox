project(ToyMath)

toy_StdReady()

file(GLOB SOURCE *.cpp)

set(LIBS toy)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_MATH)
endif()

toy_BuildLib(toy_math
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
