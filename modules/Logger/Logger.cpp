
#include <luapp.hpp>
#include <toy/Version.hpp>
#include <toy/Log.hpp>
#include <toy/Utf.hpp>
#include <toy/io/Writer.hpp>

namespace toy{
namespace luamodule{
namespace logger{

static int IsUTF8(lua::NativeState L)
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

static int Log(lua::NativeState L)
{
	PrintString(L);
	return 1;
}

static int LogWithNewLine(lua::NativeState L)
{
	PrintString(L);
	toy::Logger<<toy::NextLine;
	return 1;
}

static int Version(lua::NativeState L)
{
	lua::Table  ver;

	ver["major"] = toy::GetMajorVersion();
	ver["minor"] = toy::GetMinorVersion();
	ver["patch"] = toy::GetPatchVersion();

	lua::PushVarToLua( L, ver );

	return 1;
}

static int CleanOutputLog(lua::NativeState)
{
	toy::log::BackDefaultDevice();

	return 1;
}

static int SetOutputLog(lua::NativeState L)
{
	lua::Str   str;

	lua::CheckVarFromLua(L,&str,-1);

	lua::Pop(L,1);

	auto   dev = std::make_shared<toy::io::Writer<toy::io::Stream>>();

	dev->open(str);

	std::function<void(const char*)> func = [dev](const char* msg)
	{
		dev->printf(msg);
	};

	std::function<void(const wchar_t*)> funcw = [dev](const wchar_t* msg)
	{
		dev->printf(toy::utf::WCharToUTF8(msg));
	};

	toy::log::PushDevice(func,funcw);

	return 1;
}

}}}

#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_logger(lua::NativeState L)
{
	namespace module = ::toy::luamodule::logger;

	lua::State<>    lua(L);

	lua.setFunc( "printf", module::Log );
	lua.setFunc( "print",  module::LogWithNewLine );
	lua.setFunc( "isUTF8", module::IsUTF8 );
	lua.setFunc( "asFile", module::SetOutputLog );
	lua.setFunc( "reset",  module::CleanOutputLog );
	lua.setFunc( "version",module::Version );

	return 1;
}
