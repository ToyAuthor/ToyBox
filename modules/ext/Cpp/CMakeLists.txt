project(moduleCpp)

toy_StdReady()

file(GLOB SOURCE *.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	${TOY_libname_lua}
)

toy_BuildModule(cpp
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(cpp PROPERTIES PREFIX "")
endif()
