
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyOptions.cmake" REQUIRED)
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyBuildTools.cmake" REQUIRED)
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyThirdPartyPath.cmake" REQUIRED)
include("${TOY_ROOT_SOURCE_DIR}/cmake/ToyCheckEnvironment.cmake" REQUIRED)

macro(toy_IncludeTools)

	set(TOY_RESOURCE_PATH       ${TOY_ROOT_SOURCE_DIR}/resource)
	set(TOY_DEFAULT_INCLUDE_DIR ${TOY_ROOT_SOURCE_DIR}/include ${TOY_ROOT_SOURCE_DIR}/source)
	set(TOY_DEFAULT_LINK_DIR    ${TOY_ROOT_BINARY_DIR}/lib)

	toy_CheckEnvironment()
	toy_SetThirdPartyLibraryPath()
	toy_ProcessOptions()

endmacro(toy_IncludeTools)
