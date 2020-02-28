#include <toy/Environment.hpp>
#include <toy/ImageBuffer.hpp>
#include "Image.hpp"
#include "Stream.hpp"

static void BindFileDevice(lua::State<> *lua)
{
	namespace module = ::toy::luamodule::file;

	lua->bindMethod( "open_dir",        &module::Stream::openDir );
	lua->bindMethod( "open",            &module::Stream::open );
	lua->bindMethod( "close",           &module::Stream::close );
	lua->bindMethod( "closeDir",        &module::Stream::closeDir );
	lua->bindMethod( "make_image",      &module::Stream::makeImage );

	lua->bindMethod( "_make_sf_stream", &module::Stream::makeStream );
	lua->bindMethod( "_load_image",     &module::Stream::loadImage );
	lua->bindMethod( "_core",           &module::Stream::core );

	lua->bindClass1ArgEx<module::Stream,lua::Var>("create_stream");
}

static int CreateImageBuffer(lua::NativeState L)
{
	/*
	lua::Obj<toy::ImageBuffer>     result;
	result.ptr = new toy::ImageBuffer;
	lua::PushVarToLua( L, result );
	*/

	// It's a better way to new a toy::ImageBuffer,
	// because "toy::ImageBuffer::ImageBuffer()" doesn't need parameter.
	lua::PushClassToLua<toy::ImageBuffer>(L);

	return 1;
}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_file(lua::NativeState L)
{
	lua::State<>    lua(L);

	BindFileDevice(&lua);
	lua.cleanUnusedResource<::toy::luamodule::file::Stream>();

	lua.setFunc( "_export_png_file",          ::toy::luamodule::file::ExportPngFile );
	lua.setFunc( "create_image_buffer",          CreateImageBuffer );
//	lua.bindClass<toy::ImageBuffer>("create_image_buffer");
//	lua.cleanUnusedResource<toy::ImageBuffer>();

	return 1;
}
