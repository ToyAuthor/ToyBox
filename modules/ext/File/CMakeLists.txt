project(moduleFile)

toy_StdReady()

set(SOURCE
	File.cpp
	Stream.cpp
	Image.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	toy_file
	${TOY_libname_sfml_system}
	${TOY_libname_lua}
)

toy_BuildModule(file
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(file PROPERTIES PREFIX "")
endif()
