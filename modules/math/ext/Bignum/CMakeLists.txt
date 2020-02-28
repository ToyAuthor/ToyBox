project(moduleMathBignum)

toy_StdReady()

set(SOURCE
	Bignum.cpp
)

set(INC_DIR
	${TOY_include_gmp}
	${TOY_include_lua}
)

set(LIB_DIR
	${TOY_library_gmp}
	${TOY_library_lua}
)

set(LIBS
	toy
	toy_math
	toy_bignum
	${TOY_libname_gmp}
	${TOY_libname_lua}
)

toy_BuildModule(bignum
	INCLUDEDIRS ${INC_DIR}
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
	LIBDIRS     ${LIB_DIR}
	OUTPUTDIRS  "${TOY_ROOT_BINARY_DIR}/bin/toy/math"
)

if(UNIX OR MINGW)
	set_target_properties(bignum PROPERTIES PREFIX "")
endif()
