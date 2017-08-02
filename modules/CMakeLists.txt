
if(TOY_RELEASE)
	add_subdirectory(Logger_native)
else()
	add_subdirectory(Logger)
endif()
add_subdirectory(Window)
