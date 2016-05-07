
add_subdirectory(zlib)

# libpng need ZLIB_INCLUDE_DIR and ZLIB_LIBRARY
set(ZLIB_INCLUDE_DIR ${TOY_include_zlib})
set(ZLIB_LIBRARY     ${TOY_libname_zlib})

add_subdirectory(libpng)
