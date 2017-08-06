#include <lua.hpp>
#include <toy/Environment.hpp>

static int ToyEnv_GetOS(lua_State* L)
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

static int ToyEnv_GetCompiler(lua_State* L)
{
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

	return 1;
}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_env(lua_State* L)
{
	luaL_Reg   reg[3];

	reg[0].name = "os";
	reg[0].func = ToyEnv_GetOS;
	reg[1].name = "compiler";
	reg[1].func = ToyEnv_GetCompiler;
	reg[2].name = nullptr;
	reg[2].func = nullptr;

	luaL_newlib(L,reg);

	return 1;
}
