
include(ToyOptions)
include(ToyBuildTools)
include(ToyThirdPartyPath)
include(ToyCheckEnvironment)

macro(toy_IncludeTools)

	toy_CheckEnvironment()
	toy_SetThirdPartyLibraryPath()
	toy_ProcessOptions()

endmacro(toy_IncludeTools)
