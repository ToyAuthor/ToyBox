project(moduleWindow)

toy_StdReady()

file(GLOB SOURCE *.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	${TOY_libname_lua}
	${TOY_libname_sfml_system}
	${TOY_libname_sfml_window}
)

toy_BuildModule(window
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(window PROPERTIES PREFIX "")
endif()
