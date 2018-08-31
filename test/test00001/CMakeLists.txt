project(ToyTest00001)

toy_StdReady()

toy_BuildExe(ToyTest00001
	SOURCES     ToyTest00001.cpp
	LINKLIBS    toy toy_math
	OUTPUTDIRS  ${TOY_ROOT_BINARY_DIR}/bin
)
