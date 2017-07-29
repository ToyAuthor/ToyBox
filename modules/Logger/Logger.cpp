
#include <luapp.hpp>
#include <toy/Version.hpp>
#include <toy/Log.hpp>
#include <toy/Utf.hpp>

static int ToyBoxIsUTF8(lua::NativeState L)
{
	lua::Str   str;
	lua::CheckVarFromLua(L,&str,-1);
	lua::Pop(L,1);
	lua::Bool  result = toy::utf::IsUtf8(str);
	lua::PushVarToLua( L, result );
	return 1;
}

inline static void PrintString(lua::NativeState L)
{
	lua::Str   str;

	lua::CheckVarFromLua(L,&str,-1);
	lua::Pop(L,1);

	toy::Logger<<str;
}

static int ToyBoxLogger(lua::NativeState L)
{
	PrintString(L);
	return 1;
}

static int ToyBoxLoggerWithNewLine(lua::NativeState L)
{
	PrintString(L);
	toy::Logger<<toy::NextLine;
	return 1;
}

static int ToyBoxLoggerVersion(lua::NativeState L)
{
	lua::Table  ver;

	ver["major"] = toy::GetMajorVersion();
	ver["minor"] = toy::GetMinorVersion();
	ver["patch"] = toy::GetPatchVersion();

	lua::PushVarToLua( L, ver );

	return 1;
}

#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_logger(lua::NativeState L)
{
	lua::State<>    lua(L);

	lua.setFunc( "printf", ToyBoxLogger );
	lua.setFunc( "print",  ToyBoxLoggerWithNewLine );
	lua.setFunc( "isUTF8", ToyBoxIsUTF8 );
	lua.setFunc( "version",ToyBoxLoggerVersion );

	return 1;
}
