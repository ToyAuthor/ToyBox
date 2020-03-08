#include <luapp.hpp>
#include <toy/Environment.hpp>
#include <toy/ImageBuffer.hpp>
#include <toy/Photo.hpp>

namespace toy{
namespace luamodule{
namespace image{

static int UpsideDown(lua::NativeState L)
{
	lua::Obj<toy::ImageBuffer>   buffer;
	lua::CheckVarFromLua(L,&buffer,-1);
	lua::Pop(L,1);

	toy::photo::Flip(buffer.ptr(),toy::VERTICAL);

	return 0;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_image(lua::NativeState L)
{
	namespace module = ::toy::luamodule::image;

	lua::State<>    lua(L);

	lua.setFunc( "invert",     module::UpsideDown );

	return 1;
}
