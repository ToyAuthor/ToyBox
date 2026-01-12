project(ToyArchive)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	toy_gadget
	boost_filesystem
	boost_system
	lz4
)

include_directories(${TOY_include_lz4})

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_ARCHIVE)
endif()

toy_BuildLib(toy_archive
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${TOY_library_lz4}
)
