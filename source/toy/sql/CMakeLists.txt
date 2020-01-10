project(ToySQL)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS
	toy
	${TOY_libname_sqlite}
)

set(INC_DIR
	${TOY_include_sqlite}
)

set(LIB_DIR
	${TOY_library_sqlite}
)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_SQLITE)
endif()

toy_BuildLib(toy_sql
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
