project(moduleGraph)

toy_StdReady()

#file(GLOB SOURCE *.cpp */*.cpp)
set(SOURCE
	FileSystem.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	boost_filesystem
	boost_system
	${TOY_libname_lua}
)

toy_BuildModule(path
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(path PROPERTIES PREFIX "")
endif()
