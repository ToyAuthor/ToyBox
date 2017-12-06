
if(NOT TOY_RELEASE)
	# For test or debug.
	add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")
endif()

add_subdirectory(Player)
add_subdirectory(Interpreter)
