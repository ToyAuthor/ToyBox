project(moduleLogger)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	boost_filesystem
	boost_system
	${TOY_libname_lua}
)

toy_BuildModule(logger
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(logger PROPERTIES PREFIX "")
endif()
