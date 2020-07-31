project(PlayerGUI)

toy_StdReady()

# Hide console window
#if(MSVC)
#	if(TOY_RELEASE)
#		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#	else()
#		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#	endif()
#else()
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
#endif()

file(GLOB SOURCE *.cpp */*.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})
include_directories(${TOY_include_fltk})
link_directories(${TOY_library_fltk})

set(LIBS
	toy
	boost_filesystem
	boost_system
	${TOY_libname_lua}
	${TOY_libname_fltk}
)

#if(UNIX)
#	list(APPEND LIBS X11)
#endif()

if(TOY_ENABLE_SHARED_LIBS AND WIN32)
	add_definitions(-DLUA_BUILD_AS_DLL)
endif()

toy_BuildExe(player-gui
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
