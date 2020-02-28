project(moduleRegex)

toy_StdReady()

#file(GLOB SOURCE *.cpp */*.cpp)
set(SOURCE
	Regex.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	boost_regex
	${TOY_libname_lua}
)

toy_BuildModule(regex
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(regex PROPERTIES PREFIX "")
endif()
