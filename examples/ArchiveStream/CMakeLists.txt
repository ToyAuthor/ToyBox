project(ArchiveStream)

toy_StdReady()

add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")

set(LIBS
	toy
	toy_file
	toy_photo
	boost_filesystem
	boost_system
)

include_directories(${TOY_ROOT_SOURCE_DIR}/examples/common)

set(SOURCE
	main.cpp
)

toy_BuildExe(ArchiveStream
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
