project(FileStream)

toy_StdReady()

add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")

set(LIBS
	toy
	boost_filesystem
	boost_system
)

include_directories(${TOY_ROOT_SOURCE_DIR}/examples/common)

set(SOURCE
	main.cpp
)

toy_BuildExe(FileStream
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
