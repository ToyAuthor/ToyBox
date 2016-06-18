project(FileSystem)

toy_StdReady()

add_definitions(-DGLEW_STATIC)
include_directories(${TOY_include_glew})
link_directories(${TOY_library_glew})


include_directories(${TOY_include_freetype})
link_directories(${TOY_library_freetype})

add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")

set(LIBS
	toy
	toy_file
	toy_scene
	${TOY_libname_sfml_system}
	${TOY_libname_sfml_window}
	${TOY_libname_freetype}
)

if(NOT TOY_ANDROID)
	list(APPEND LIBS ${TOY_libname_glew})
endif()

if(APPLE)
	find_library(TOY_FW_OpenGL OpenGL)
	list(APPEND LIBS ${TOY_FW_OpenGL})
#	list(APPEND LIBS "-framework OpenGL")
elseif(TOY_ANDROID)
	list(APPEND LIBS GLESv2 GLESv1_CM EGL)
elseif(UNIX)
	list(APPEND LIBS GL X11)
elseif(WIN32)
	list(APPEND LIBS opengl32 gdi32)
endif()

file(GLOB SOURCE *.cpp */*.cpp)

toy_BuildExe(FileSystem
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
