project(ToyBignum)

toy_StdReady()

file(GLOB SOURCE *.cpp */*.cpp)

set(LIBS toy
	toy_math
	${TOY_libname_gmp}
)

set(INC_DIR
	${TOY_include_gmp}
)

set(LIB_DIR
	${TOY_library_gmp}
)

if(TOY_ENABLE_SHARED_LIBS)
	add_definitions(-DTOY_EXPORT_BIGNUM)
endif()

toy_BuildLib(toy_bignum
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
)
