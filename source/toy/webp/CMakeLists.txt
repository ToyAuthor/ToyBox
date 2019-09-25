project(ToyWebp)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS
	toy
	toy_file
	webp
	webpdemux
#	webpdecoder
#	webpmux
)

set(INC_DIR
	${TOY_include_webp}
)

set(LIB_DIR
	${TOY_library_webp}
)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_WEBP)
endif()

toy_BuildLib(toy_webp
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
