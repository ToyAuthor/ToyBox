project(moduleFileLoaderWebp)

toy_StdReady()

set(SOURCE
	Webp.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

include_directories(${TOY_include_webp})
link_directories(${TOY_library_webp})

set(LIBS
	toy
	toy_file
	toy_webp
	${TOY_libname_lua}
)

toy_BuildModule(webp_temp
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	OUTPUTDIRS  "${TOY_ROOT_BINARY_DIR}/bin/toy/file/loader/"
)

if(UNIX OR MINGW)
	set_target_properties(webp_temp PROPERTIES PREFIX "")
endif()

set_target_properties(webp_temp PROPERTIES OUTPUT_NAME "webp")
