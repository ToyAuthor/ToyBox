project(ToyGadget)

toy_StdReady()

file(GLOB SOURCE *.cpp)

set(LIBS toy)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_GADGET)
endif()

toy_BuildLib(toy_gadget
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)
