project(moduleSplit)

toy_StdReady()

#file(GLOB SOURCE *.cpp */*.cpp)
set(SOURCE
	Split.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	toy_parser
	${TOY_libname_lua}
)
#set(MY_PROJECT_NAME "split")

toy_BuildModule(split
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(split PROPERTIES PREFIX "")
endif()
