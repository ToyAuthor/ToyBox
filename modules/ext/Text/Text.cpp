#include <cctype>
#include <algorithm>
#include <luapp.hpp>
#include <toy/Environment.hpp>
#include <toy/Log.hpp>
#include <toy/bignum/Num.hpp>
#include <toy/gadget/AnsiNumToStr.hpp>
#include <toy/gadget/StrToAscii.hpp>

namespace toy{
namespace luamodule{
namespace text{

static lua::Str    ErrorMessage;
static lua::Bool   ErrorFlag = false;

static inline void HandleError(lua::NativeState L, const char *msg, std::exception &e)
{
	toy::Log(e);
	ErrorFlag = true;
	ErrorMessage = msg;
	lua::PushVarToLua( L, lua::Nil() );
}

static int IsGood(lua::NativeState L)
{
	lua::PushVarToLua( L, !ErrorFlag );

	return 1;
}

static int ReportError(lua::NativeState L)
{
	lua::PushVarToLua( L, ErrorMessage );

	return 1;
}

static int ToUpper(lua::NativeState L)
{
	lua::Str   str;

	try
	{
		ErrorFlag = false;

		lua::CheckVarFromLua(L,&str,-1);
		lua::Pop(L,1);

		std::transform( str.begin(), str.end(), str.begin(), toupper );
	}
	catch(std::exception &e)
	{
		HandleError(L,"Convert string to uppercase failed",e);
		return 0;
	}

	lua::PushVarToLua( L, str );

	return 1;
}

static int ToLower(lua::NativeState L)
{
	lua::Str   str;

	try
	{
		ErrorFlag = false;

		lua::CheckVarFromLua(L,&str,-1);
		lua::Pop(L,1);

		std::transform( str.begin(), str.end(), str.begin(), tolower );
	}
	catch(std::exception &e)
	{
		HandleError(L,"Convert string to lowercase failed",e);
		return 0;
	}

	lua::PushVarToLua( L, str );

	return 1;
}

static int AnsiToStr(lua::NativeState L)
{
	lua::Str   str;

	try
	{
		ErrorFlag = false;

		lua::Int   num;

		lua::CheckVarFromLua(L,&num,-1);
		lua::Pop(L,1);

		str = toy::gadget::AnsiNumToStr(num);
	}
	catch(std::exception &e)
	{
		HandleError(L,"Convert ansi code to string failed",e);
		return 0;
	}

	lua::PushVarToLua( L, str );

	return 1;
}

static int StrToAscii(lua::NativeState L)
{
	lua::Int   num;

	try
	{
		ErrorFlag = false;

		lua::Str   str;

		lua::CheckVarFromLua(L,&str,-1);
		lua::Pop(L,1);

		num = toy::gadget::StrToAscii(str);
	}
	catch(std::exception &e)
	{
		HandleError(L,"Convert string code to ascii code failed",e);
		return 0;
	}

	lua::PushVarToLua( L, num );

	return 1;
}

static int StrToNum(lua::NativeState L)
{
	lua::Num   num;

	try
	{
		ErrorFlag = false;

		lua::Str   str;
		double     bigfloat = 0;

		lua::CheckVarFromLua(L,&str,-1);
		lua::Pop(L,1);
		toy::bignum::Num  dev(str);
		dev.get(&bigfloat);
		num = bigfloat;
	}
	catch(std::exception &e)
	{
		HandleError(L,"Convert string to number failed",e);
		return 0;
	}

	lua::PushVarToLua( L, num );

	return 1;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_text(lua::NativeState L)
{
	namespace module = ::toy::luamodule::text;

	module::ErrorMessage = "good";

	lua::State<>    lua(L);

	lua.setFunc( "good",          module::IsGood );
	lua.setFunc( "error",         module::ReportError );
	lua.setFunc( "toupper",       module::ToUpper );
	lua.setFunc( "tolower",       module::ToLower );
	lua.setFunc( "ansi_to_str",   module::AnsiToStr );
	lua.setFunc( "str_to_ascii",  module::StrToAscii );
	lua.setFunc( "str_to_num",    module::StrToNum );

	return 1;
}
