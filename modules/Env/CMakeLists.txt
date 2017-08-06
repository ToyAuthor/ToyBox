project(moduleEnvironment)

toy_StdReady()

set(SOURCE Environment.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	${TOY_libname_lua}
)

toy_BuildModule(env
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(env PROPERTIES PREFIX "")
endif()
