project(HelloWorld)

toy_StdReady()

toy_BuildExe(HelloWorld
	SOURCES     HelloWorld.cpp
	LINKLIBS    toy toy_root
	OUTPUTDIRS  ${TOY_ROOT_BINARY_DIR}/bin
)
