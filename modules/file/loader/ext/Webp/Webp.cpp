
#include <luapp.hpp>
#include <toy/Environment.hpp>
#include <toy/ImageBuffer.hpp>
#include <toy/Exception.hpp>
#include <toy/File.hpp>
#include <toy/webp/LoadFile.hpp>

namespace toy{
namespace luamodule{
namespace webp{

static int LoadWebp(lua::NativeState L)
{
	//                                                 ... [obj] [buffer]
	lua::Obj<std::shared_ptr<toy::File>>   io;
	lua::Obj<toy::ImageBuffer>             image;
	lua::Str                               str("_core");

	lua::CheckVarFromLua(L,&image,-1);
	lua::PushVarToLua( L, str );                    // ... [obj] [buffer] ["_core"]
	lua::GetTable(L,-3);                            // ... [obj] [buffer] [func]
	lua::PushValue(L,-3);                           // ... [obj] [buffer] [func] [obj]
	lua::Call(L,1,1);                               // ... [obj] [buffer] [toy::File]
	lua::CheckVarFromLua(L,&io,-1);
	lua::Pop(L,3);                                  // ...

	if ( false == toy::webp::LoadWebp( io.ref().get(), image.ptr() ) )
	{
		throw toy::Exception(TOY_MARK);
	}

	return 0;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_file_loader_webp(lua::NativeState L)
{
	namespace module = ::toy::luamodule::webp;

	lua::State<>    lua(L);

	lua.setFunc( "load_image",          module::LoadWebp );

	return 1;
}
