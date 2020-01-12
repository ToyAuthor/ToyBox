#include <luapp.hpp>
#include <toy/Environment.hpp>
#include <toy/Oops.hpp>
#include <toy/Log.hpp>

namespace toy{
namespace luamodule{
namespace cpp{

static int CatchException(lua::NativeState L)
{
	lua::Bool result = false;

	try
	{
		lua::Call(L,0,0);
	}
	catch(std::exception &e)
	{
		result = true;
		toy::Log(e);
		toy::Oops(TOY_MARK);
	}

	lua::PushVarToLua( L, result );

	return 1;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_cpp(lua::NativeState L)
{
	namespace module = ::toy::luamodule::cpp;

	lua::State<>    lua(L);

	lua.setFunc( "catch",         module::CatchException );

	return 1;
}
