project(moduleAudio)

toy_StdReady()

set(SOURCE Audio.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	${TOY_libname_sfml_system}
	${TOY_libname_sfml_audio}
	${TOY_libname_lua}
)

toy_BuildModule(audio
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(audio PROPERTIES PREFIX "")
endif()
