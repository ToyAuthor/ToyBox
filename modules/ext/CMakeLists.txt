
if(TOY_RELEASE)
	add_subdirectory(Logger_native)
else()
	add_subdirectory(Logger)
	add_subdirectory(Window)
endif()

add_subdirectory(Cpp)
add_subdirectory(Env)
