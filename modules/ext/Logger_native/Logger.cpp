
#include <lua.hpp>
#include <toy/Log.hpp>
#include <toy/Utf.hpp>
#include <toy/io/Writer.hpp>

namespace toy{
namespace luamodule{
namespace logger{

static int IsUTF8(lua_State* L)
{
	std::string    str;

	if ( lua_type(L, -1)==LUA_TSTRING )
	{
		str = lua_tostring(L,-1);
	}
	else
	{
		toy::Logger << "warning:toy.logger can't check non-string variable!" << toy::NewLine;
	}

	lua_pop(L,1);

	auto  result = toy::utf::IsUtf8(str);

	lua_pushboolean(L,(int)result);

	return 1;
}

static inline void PrintString(lua_State* L)
{
	if ( lua_type(L, -1)==LUA_TSTRING )
	{
		toy::Logger<<lua_tostring(L,-1);
	//	toy::Logger<<luaL_checkstring(L,-1);
	}
	else
	{
		toy::Logger << "warning:toy.logger can't print non-string variable!" << toy::NewLine;
	}

	lua_pop(L,1);
}

static int Log(lua_State* L)
{
	PrintString(L);
	return 0;
}

static int LogWithNewLine(lua_State* L)
{
	PrintString(L);
	toy::Logger<<toy::NewLine;
	return 0;
}

static int SetOutputLog(lua_State* L)
{
	std::string    str;

	if ( lua_type(L, -1)==LUA_TSTRING )
	{
		str = lua_tostring(L,-1);
	}
	else
	{
		toy::Logger << "warning:toy.logger can't take non-string variable as file name!" << toy::NewLine;
	}

	lua_pop(L,1);

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

static int CleanOutputLog(lua_State*)
{
	toy::log::BackDefaultDevice();
	return 1;
}

}}}

#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_logger(lua_State* L)
{
	namespace module = ::toy::luamodule::logger;

	luaL_Reg   reg[6];

	reg[0].name = "printf";
	reg[0].func = module::Log;
	reg[1].name = "print";
	reg[1].func = module::LogWithNewLine;
	reg[2].name = "is_utf8";
	reg[2].func = module::IsUTF8;
	reg[3].name = "as_file";
	reg[3].func = module::SetOutputLog;
	reg[4].name = "reset";
	reg[4].func = module::CleanOutputLog;
	reg[5].name = nullptr;
	reg[5].func = nullptr;

	luaL_newlib(L,reg);

	return 1;
}
