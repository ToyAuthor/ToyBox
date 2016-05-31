project(Toy)


toy_StdReady()


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT)
endif()

file(GLOB SOURCE
	*.cpp
	utf/*.cpp
)

set(LIB pthread)

if(APPLE)
	list(APPEND LIB iconv)
endif()

if(UNIX)
	toy_BuildLib(toy
		SOURCES     ${SOURCE}
		LINKLIBS    ${LIB}
	)
else()
	toy_BuildLib(toy
		SOURCES     ${SOURCE}
	)
endif()


add_subdirectory(root)
add_subdirectory(file)
add_subdirectory(parser)
add_subdirectory(graph)
