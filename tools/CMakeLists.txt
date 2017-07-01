
if(NOT TOY_RELEASE)
	# For test or debug.
	add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")
endif()

# They are OK on Android. Just ignore them.
if(NOT TOY_ANDROID)
if(TOY_ENABLE_SHARED_LIBS)
	add_subdirectory(Player)
endif()
endif()
