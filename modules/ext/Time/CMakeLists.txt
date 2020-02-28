project(moduleTime)

toy_StdReady()

set(SOURCE Time.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy_time
	${TOY_libname_lua}
)

toy_BuildModule(time
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(time PROPERTIES PREFIX "")
endif()
