
# The complete list of third-party libraries:"ToyBox/third-party/readme.txt"
macro(toy_SetThirdPartyLibraryPath)

	if(APPLE)
		set(TOY_SDK_INC         "$ENV{HOME}/ToyBoxSDK/include" )
		set(TOY_SDK_LIB         "$ENV{HOME}/ToyBoxSDK/lib/mac_llvmgcc_x64_release" )
	elseif(MSVC)
		set(TOY_SDK_INC         "D:/ToyBoxSDK/include" )
		set(TOY_SDK_LIB         "D:/ToyBoxSDK/lib/msvc2015_x64_release" )
	elseif(WIN32)
		set(TOY_SDK_INC         "D:/ToyBoxSDK/include" )
		set(TOY_SDK_LIB         "D:/ToyBoxSDK/lib/tdm_gcc_x64_release" )
	elseif(UNIX)
		set(TOY_SDK_INC         "$ENV{HOME}/ToyBoxSDK/include" )
		set(TOY_SDK_LIB         "$ENV{HOME}/ToyBoxSDK/lib/ubuntu_gcc_x64_release" )
	endif()

	if(NOT EXISTS ${TOY_SDK_INC} AND NOT EXISTS ${TOY_SDK_LIB})
		# TOY_SDK_INC and TOY_SDK_LIB is not necessary.
		# You can just modify the following paths and ignore this error.
		# Take a look!
		# https://github.com/ToyAuthor/ToyBoxSDK
		message(FATAL_ERROR "ToyBox:Are you sure you have all the third-party libraries?")
	endif()

	#---------------------------------------------------------------------------

	set(TOY_include_boost       "${TOY_SDK_INC}" )
	set(TOY_library_boost       "${TOY_ROOT_BINARY_DIR}/third-party/boost" )


	set(TOY_include_lua         "${TOY_ROOT_SOURCE_DIR}/third-party/lua" )
	set(TOY_library_lua         "${TOY_ROOT_BINARY_DIR}/third-party/lua" )
	set(TOY_libname_lua         "lua" )


	set(TOY_include_zlib        "${TOY_ROOT_SOURCE_DIR}/third-party/zlib" "${TOY_ROOT_BINARY_DIR}/third-party/zlib" )
	set(TOY_library_zlib        "${TOY_ROOT_BINARY_DIR}/third-party/zlib" )
	set(TOY_libname_zlib        "zlib" )


	if(UNIX)
	set(TOY_include_7zip        "${TOY_ROOT_SOURCE_DIR}/third-party/p7zip" )
	set(TOY_library_7zip        "${TOY_ROOT_BINARY_DIR}/third-party/p7zip" )
	set(TOY_libname_7zip        "p7zip" )
	else()
	set(TOY_include_7zip        "${TOY_ROOT_SOURCE_DIR}/third-party/7zip" )
	set(TOY_library_7zip        "${TOY_ROOT_BINARY_DIR}/third-party/7zip" )
	set(TOY_libname_7zip        "7zip" )
	endif()


	set(TOY_include_glew        "${TOY_ROOT_SOURCE_DIR}/third-party/glew/include" )
	set(TOY_library_glew        "${TOY_ROOT_BINARY_DIR}/third-party/glew" )
	set(TOY_libname_glew        "glew" )


	set(TOY_include_asio        "${TOY_SDK_INC}" )

	set(TOY_include_glm         "${TOY_ROOT_SOURCE_DIR}/third-party/glm" )

	set(TOY_include_json        "${TOY_ROOT_SOURCE_DIR}/third-party/json" )


	set(TOY_library_gmp         "${TOY_SDK_LIB}/GMP" )
	set(TOY_include_gmp         "${TOY_SDK_LIB}/GMP" )
	if(MSVC)
	set(TOY_libname_gmp         "mpir" )
	else()
	set(TOY_libname_gmp         "gmp" )
	endif()


	set(TOY_include_freetype    "${TOY_SDK_INC}/freetype" )
	set(TOY_library_freetype    "${TOY_SDK_LIB}/freetype" )
	set(TOY_libname_freetype    "freetype" )


	set(TOY_include_libpng      "${TOY_SDK_INC}/libpng" "${TOY_SDK_LIB}/libpng" )
	set(TOY_library_libpng      "${TOY_SDK_LIB}/libpng" )
	if(MSVC)
	set(TOY_libname_libpng      "libpng" )
	else()
	set(TOY_libname_libpng      "png" )
	endif()


	set(TOY_include_sfml        "${TOY_SDK_INC}" )
	set(TOY_library_sfml        "${TOY_SDK_LIB}/SFML" )
	set(TOY_libname_sfml_main   "sfml-main" )
	set(TOY_libname_sfml_system "sfml-system" )
	set(TOY_libname_sfml_window "sfml-window" )
	set(TOY_libname_sfml_graph  "sfml-graphics" )
	set(TOY_libname_sfml_audio  "sfml-audio" )
	set(TOY_libname_sfml_network"sfml-network" )


	set(TOY_include_fltk        "${TOY_SDK_INC}" )
	set(TOY_library_fltk        "${TOY_SDK_LIB}/FLTK" )
	set(TOY_libname_fltk        "fltk_SHARED" )

endmacro(toy_SetThirdPartyLibraryPath)
