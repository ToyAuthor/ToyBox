/*
 * Give you some information about environment and player itself.
 */

#include <lua.hpp>
#include <boost/config.hpp>
#include <toy/Version.hpp>
#include <toy/Environment.hpp>

namespace toy{
namespace luamodule{
namespace env{

/*static int Version(lua::NativeState L)
{
	lua::Table  ver;

	ver["major"] = toy::GetMajorVersion();
	ver["minor"] = toy::GetMinorVersion();
	ver["patch"] = toy::GetPatchVersion();

	lua::PushVarToLua( L, ver );

	return 1;
}*/
static int Version(lua_State* L)
{
	auto   setValue = [L](const char* key,lua_Integer value)
	{
		lua_pushstring(L, key);      // ... [T] [key]
		lua_pushinteger(L, value);   // ... [T] [key] [value]
		lua_settable(L,-3);          // ... [T]
	};

	                    // ...
	lua_newtable(L);    // ... [T]

	setValue("major",toy::GetMajorVersion());
	setValue("minor",toy::GetMinorVersion());
	setValue("patch",toy::GetPatchVersion());

	                    // ... [T]
	return 1;
}

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

static int GetSizeOfNumber(lua_State* L)
{
	lua_pushinteger(L,static_cast<lua_Integer>(sizeof(lua_Number)));

	return 1;
}

static int GetSizeOfInteger(lua_State* L)
{
	lua_pushinteger(L,static_cast<lua_Integer>(sizeof(lua_Integer)));

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

	luaL_Reg   reg[6];

	reg[0].name = "get_player_version";
	reg[0].func = module::Version;
	reg[1].name = "os";
	reg[1].func = module::GetOS;
	reg[2].name = "compiler";
	reg[2].func = module::GetCompiler;
	reg[3].name = "get_size_of_lua_number";
	reg[3].func = module::GetSizeOfNumber;
	reg[4].name = "get_size_of_lua_integer";
	reg[4].func = module::GetSizeOfInteger;
	reg[5].name = nullptr;
	reg[5].func = nullptr;

	luaL_newlib(L,reg);

	return 1;
}
