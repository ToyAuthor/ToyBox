project(Database)

toy_StdReady()

set(LIBS
	toy
	toy_sql
	boost_filesystem
	boost_system
)

set(SOURCE
	Database.cpp
)

toy_BuildExe(Database
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
