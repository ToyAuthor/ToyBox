
set(TOY_ENABLE_3RD_PARTY_SHARED_LIB ${TOY_ENABLE_SHARED_LIBS})


if(TOY_ENABLE_3RD_PARTY_SHARED_LIB)
	set(TOY_3RD_PARTY_LIB_TYPE SHARED)
else()
	set(TOY_3RD_PARTY_LIB_TYPE STATIC)
endif()


add_subdirectory(lua)
add_subdirectory(boost)
add_subdirectory(zlib)
add_subdirectory(lz4)


if(UNIX)
	add_subdirectory(p7zip)
else()
	add_subdirectory(7zip)
endif()

if(TOY_USE_GLEW)
	add_subdirectory(glew)
endif()
