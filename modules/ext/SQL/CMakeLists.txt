project(moduleSQL)

toy_StdReady()

set(SOURCE
	SQLite.cpp
)

include_directories(${TOY_include_sqlite})
link_directories(${TOY_library_sqlite})

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
#	toy_sql
	${TOY_libname_sqlite}
	${TOY_libname_lua}
)

toy_BuildModule(sql
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(sql PROPERTIES PREFIX "")
endif()
