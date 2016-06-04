project(UnicodeTest)

toy_StdReady()

toy_BuildExe(UnicodeTest
	SOURCES     UnicodeTest.cpp
	LINKLIBS    toy toy_root
	OUTPUTDIRS  ${TOY_ROOT_BINARY_DIR}/bin
)
