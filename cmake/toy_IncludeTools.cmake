
macro(toy_IncludeTools)

	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_ProcessOptions.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_StdReady.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_Option.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_ProcessArguments.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_BuildLib.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_BuildExe.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_BuildModule.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_SetThirdPartyLibraryPath.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_CheckEnvironment.cmake" REQUIRED)

	set(TOY_RESOURCE_PATH       ${TOY_ROOT_SOURCE_DIR}/resource)
	set(TOY_DEFAULT_INCLUDE_DIR ${TOY_ROOT_SOURCE_DIR}/include ${TOY_ROOT_SOURCE_DIR}/source)
	set(TOY_DEFAULT_LINK_DIR    ${TOY_ROOT_BINARY_DIR}/lib)

	toy_Option()
	toy_CheckEnvironment()
	toy_SetThirdPartyLibraryPath()
	toy_ProcessOptions()

endmacro(toy_IncludeTools)
