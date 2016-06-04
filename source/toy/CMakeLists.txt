project(Toy)


toy_StdReady()


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT)
endif()

file(GLOB SOURCE
	*.cpp
	utf/*.cpp
	log/*.cpp
)

if(TOY_ANDROID)
	set(LIB log android)
	toy_BuildLib(toy
		SOURCES     ${SOURCE}
		LINKLIBS    ${LIB}
	)
elseif(UNIX)
	set(LIB pthread)
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

if(NOT TOY_ANDROID)
add_subdirectory(graph)
endif()
