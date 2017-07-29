project(UnicodeTest)

toy_StdReady()

toy_BuildExe(UnicodeTest
	SOURCES     UnicodeTest.cpp
	LINKLIBS    toy
	OUTPUTDIRS  ${TOY_ROOT_BINARY_DIR}/bin
)
