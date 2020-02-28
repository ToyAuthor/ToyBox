project(moduleText)

toy_StdReady()

file(GLOB SOURCE *.cpp)

include_directories(${TOY_include_lua})
include_directories(${TOY_include_gmp})
link_directories(${TOY_library_lua})
link_directories(${TOY_library_gmp})

set(LIBS
	toy
	toy_gadget
	toy_math
	toy_bignum
	${TOY_libname_gmp}
	${TOY_libname_lua}
)

toy_BuildModule(text
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

if(UNIX OR MINGW)
	set_target_properties(text PROPERTIES PREFIX "")
endif()
