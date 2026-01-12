project(ToyPhoto)

toy_StdReady()

file(GLOB SOURCE *.cpp)

set(LIBS toy)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_PHOTO)
endif()

toy_BuildLib(toy_photo
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
