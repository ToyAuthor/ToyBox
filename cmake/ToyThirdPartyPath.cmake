
macro(toy_SetThirdPartyLibraryPath)

	if(WIN32)
		set(TOY_include_sfml        "D:/sdk/SFML/include" )
		set(TOY_library_sfml        "D:/sdk/SFML/lib" )
	elseif(UNIX)
		set(TOY_include_sfml        "~/sdk/SFML/include" )
		set(TOY_library_sfml        "~/sdk/SFML/lib" )
	endif()

	set(TOY_libname_sfml_main       "sfml-main" )
	set(TOY_libname_sfml_system     "sfml-system" )
	set(TOY_libname_sfml_window     "sfml-window" )
	set(TOY_libname_sfml_graphics   "sfml-graphics" )
	set(TOY_libname_sfml_audio      "sfml-audio" )
	set(TOY_libname_sfml_network    "sfml-network" )


	set(TOY_include_zlib        "${TOY_ROOT_SOURCE_DIR}/third-party/zlib" "${TOY_ROOT_BINARY_DIR}/third-party/zlib" )
	set(TOY_library_zlib        "${TOY_ROOT_BINARY_DIR}/third-party/zlib" )
	set(TOY_libname_zlib        "zlib" )


	set(TOY_include_libpng      "${TOY_ROOT_SOURCE_DIR}/third-party/libpng" "${TOY_ROOT_BINARY_DIR}/third-party/libpng" )
	set(TOY_library_libpng      "${TOY_ROOT_BINARY_DIR}/third-party/libpng" )
	set(TOY_libname_libpng      "png" )

endmacro(toy_SetThirdPartyLibraryPath)
