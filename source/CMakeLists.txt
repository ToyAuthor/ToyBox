project(Toy)

toy_StdReady()

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT)
endif()

file(GLOB SOURCE
	toy/*.cpp
	toy/utf/*.cpp
	toy/log/*.cpp
	toy/path/*.cpp
	toy/io/*.cpp
)

set(LIB
	boost_filesystem
	boost_system
)

if(TOY_ANDROID)
	list(APPEND LIBS log android)
elseif(UNIX)
	list(APPEND LIB pthread)
endif()

toy_BuildLib(toy
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIB}
)

# No, it doesn't work on Visual Studio 2015.
#add_subdirectory(toy)
