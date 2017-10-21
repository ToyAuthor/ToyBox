project(Toy)


toy_StdReady()


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT)
endif()

file(GLOB SOURCE
	toy/*.cpp
	toy/utf/*.cpp
	toy/log/*.cpp
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

# No, it doesn't work on Visual Studio 2015.
#add_subdirectory(toy)
