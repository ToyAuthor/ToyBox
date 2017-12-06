project(LuaInterpreter)

toy_StdReady()

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	#toy
	${TOY_libname_lua}
)

if(TOY_ENABLE_SHARED_LIBS AND WIN32)
	add_definitions(-DLUA_BUILD_AS_DLL)
endif()

toy_BuildExe(luaTag
	SOURCES     main.cpp
	LINKLIBS    ${LIBS}
)

set_target_properties(luaTag PROPERTIES OUTPUT_NAME lua)
