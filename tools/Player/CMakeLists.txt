project(Player)

file(COPY ${PROJECT_SOURCE_DIR}/default-config.lua DESTINATION ${TOY_ROOT_BINARY_DIR}/bin/)

toy_StdReady()

# Hide console window
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")

file(GLOB SOURCE *.cpp */*.cpp)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	toy_root
	boost_filesystem
	boost_system
	${TOY_libname_lua}
)

if(TOY_ENABLE_SHARED_LIBS AND WIN32)
	add_definitions(-DLUA_BUILD_AS_DLL)
endif()

toy_BuildExe(ToyBoxPlayer
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
