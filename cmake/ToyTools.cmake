
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyOptions.cmake" REQUIRED)
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyBuildTools.cmake" REQUIRED)
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyThirdPartyPath.cmake" REQUIRED)
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyCheckEnvironment.cmake" REQUIRED)

macro(toy_IncludeTools)

	toy_CheckEnvironment()
	toy_SetThirdPartyLibraryPath()
	toy_ProcessOptions()

endmacro(toy_IncludeTools)
