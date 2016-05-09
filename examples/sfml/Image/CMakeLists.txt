project(SfmlImage)

toy_StdReady()

include_directories(${TOY_include_sfml})
link_directories(${TOY_library_sfml})

add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")



set(LIBS
	${TOY_libname_sfml_system}
	${TOY_libname_sfml_window}
)

if(APPLE)
	find_library(TOY_FW_OpenGL OpenGL)
	list(APPEND LIBS ${TOY_FW_OpenGL})
#	list(APPEND LIBS "-framework OpenGL")
elseif(UNIX)
	list(APPEND LIBS GL GLU X11)
elseif(WIN32)
	list(APPEND LIBS opengl32 glu32 gdi32)
endif()



toy_BuildExe(SfmlImage
	SOURCES     main.cpp
	LINKLIBS    ${LIBS}
)
