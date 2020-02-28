
file(GLOB MY_TOY_LUA_AUXILIARY "${CMAKE_CURRENT_SOURCE_DIR}/*.lua" )
file(COPY ${MY_TOY_LUA_AUXILIARY} DESTINATION ${TOY_ROOT_BINARY_DIR}/bin/toy/file/loader/)

add_subdirectory(ext)
