


macro(toy_IncludeTools)

	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_ProcessOptions.cmake" REQUIRED)
	if(TOY_ANDROID)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/android/create_apk.cmake" REQUIRED)
	endif()
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_StdReady.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_ProcessArguments.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_BuildLib.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_BuildExe.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_BuildModule.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_SetThirdPartyLibraryPath.cmake" REQUIRED)
	include("${TOY_ROOT_SOURCE_DIR}/cmake/toy_CheckEnvironment.cmake" REQUIRED)

	if(NOT CMAKE_BUILD_TYPE)
	#	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
		set(CMAKE_BUILD_TYPE "Debug"   CACHE STRING "Choose the type of build" FORCE)
	endif()

	option( TOY_ENABLE_SHARED_LIBS   "Make shared library"                  ON )
	set(    TOY_USE_GLEW                                                    ON )

	set(TOY_RESOURCE_PATH       ${TOY_ROOT_SOURCE_DIR}/resource)
	set(TOY_DEFAULT_INCLUDE_DIR ${TOY_ROOT_SOURCE_DIR}/include ${TOY_ROOT_SOURCE_DIR}/source)
	set(TOY_DEFAULT_LINK_DIR    ${TOY_ROOT_BINARY_DIR}/lib)

	toy_CheckEnvironment()
	toy_SetThirdPartyLibraryPath()
	toy_ProcessOptions()

endmacro(toy_IncludeTools)
