/*
 * Print message on terminal or user given target.
 */

#include <luapp.hpp>
#include <toy/Oops.hpp>
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
	lua::PushVarToLua( L, static_cast<lua::Bool>(toy::utf::IsUtf8(str)) );
	return 1;
}

static inline void PrintString(lua::NativeState L)
{
	lua::Str   str;

	if ( lua::IsType<lua::Str>(L,-1) )
	{
		lua::CheckVarFromLua(L,&str,-1);
	}
	else
	{
		toy::Oops(TOY_MARK);
		str = "[Error]";
	}

	lua::Pop(L,1);

	toy::Logger<<str;
}

static int Log(lua::NativeState L)
{
	PrintString(L);
	return 0;
}

static int LogWithNewLine(lua::NativeState L)
{
	PrintString(L);
	toy::Logger<<toy::NewLine;
	return 0;
}

static int CleanOutputLog(lua::NativeState)
{
	toy::log::BackDefaultDevice();

	return 0;
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

	return 0;
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

	lua.setFunc( "printf",      module::Log );
	lua.setFunc( "print",       module::LogWithNewLine );
	lua.setFunc( "is_utf8",     module::IsUTF8 );
	lua.setFunc( "as_file",     module::SetOutputLog );
	lua.setFunc( "reset",       module::CleanOutputLog );

	return 1;
}
