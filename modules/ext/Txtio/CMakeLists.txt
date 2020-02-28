project(moduleTxtio)

toy_StdReady()

set(SOURCE
	Txtio.cpp
	ReaderWrapper.cpp
	WriterWrapper.cpp
)

include_directories(${TOY_include_lua})
link_directories(${TOY_library_lua})

set(LIBS
	toy
	toy_parser
	${TOY_libname_lua}
)

toy_BuildModule(txtio
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(txtio PROPERTIES PREFIX "")
endif()
