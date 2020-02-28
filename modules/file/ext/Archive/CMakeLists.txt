project(moduleFileArchive)

toy_StdReady()

set(SOURCE
	Archive.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	toy_file
	${TOY_libname_lua}
)

toy_BuildModule(archive
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	OUTPUTDIRS  "${TOY_ROOT_BINARY_DIR}/bin/toy/file/"
)

if(UNIX OR MINGW)
	set_target_properties(archive PROPERTIES PREFIX "")
endif()
