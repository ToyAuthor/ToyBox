#include <lua.hpp>
#include <boost/config.hpp>
#include <toy/Environment.hpp>

namespace toy{
namespace luamodule{
namespace env{

static int GetOS(lua_State* L)
{
	#if defined(TOY_LINUX)
		lua_pushstring(L, "linux");
	#elif defined(TOY_MAC)
		lua_pushstring(L, "mac");
	#elif defined(TOY_WINDOWS)
		lua_pushstring(L, "windows");
	#else
		lua_pushstring(L, "unknown");
	#endif

	return 1;
}

static int GetCompiler(lua_State* L)
{
	lua_pushstring(L,BOOST_COMPILER);
/*
	#if defined(TOY_GCC)
		lua_pushstring(L, "GCC");
	#elif defined(TOY_MINGW)
		lua_pushstring(L, "MinGW");
	#elif defined(TOY_LLVM)
		lua_pushstring(L, "LLVM-GCC");
	#elif defined(TOY_VC_2015)
		lua_pushstring(L, "Visual Studio 2015");
	#elif defined(TOY_MSVC)
		lua_pushstring(L, "Visual Studio");
	#else
		lua_pushstring(L, "unknown");
	#endif
*/
	return 1;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_env(lua_State* L)
{
	namespace module = ::toy::luamodule::env;

	luaL_Reg   reg[3];

	reg[0].name = "os";
	reg[0].func = module::GetOS;
	reg[1].name = "compiler";
	reg[1].func = module::GetCompiler;
	reg[2].name = nullptr;
	reg[2].func = nullptr;

	luaL_newlib(L,reg);

	return 1;
}
