project(moduleImage)

toy_StdReady()

set(SOURCE
	ImageProcessing.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	toy_photo
	${TOY_libname_lua}
)

toy_BuildModule(image
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(image PROPERTIES PREFIX "")
endif()
