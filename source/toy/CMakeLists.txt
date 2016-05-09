project(Toy)


toy_StdReady()


if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT)
endif()


set(SOURCE
	Log.cpp
	Image.cpp
	Character.cpp
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
