
# Copy "ToyBox/modules/*.lua" to "ToyBox/build/bin/toy".
file(GLOB MY_TOY_LUA_AUXILIARY "${CMAKE_CURRENT_SOURCE_DIR}/*.lua" )
file(COPY ${MY_TOY_LUA_AUXILIARY} DESTINATION ${TOY_ROOT_BINARY_DIR}/bin/toy/text/)

if(TOY_ENABLE_ALPHA_API)
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/beta)
		file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/beta DESTINATION ${TOY_ROOT_BINARY_DIR}/bin/toy/text/)
	endif()
endif()
