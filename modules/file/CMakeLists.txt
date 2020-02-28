
file(GLOB MY_TOY_LUA_AUXILIARY "${CMAKE_CURRENT_SOURCE_DIR}/*.lua" )
file(COPY ${MY_TOY_LUA_AUXILIARY} DESTINATION ${TOY_ROOT_BINARY_DIR}/bin/toy/file/)

add_subdirectory(ext)
add_subdirectory(loader)
add_subdirectory(export)
add_subdirectory(io)
