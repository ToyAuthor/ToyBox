#include <memory>
#include <luapp.hpp>
#include <toy/Environment.hpp>
#include <toy/Oops.hpp>
#include <toy/bignum/Int.hpp>
#include <toy/bignum/Num.hpp>
#include "BindIntegerMake.hpp"
#include "BindFloatMake.hpp"

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_math_bignum(lua::NativeState L)
{
	namespace module = ::toy::luamodule::bignum;

	lua::State<>    lua(L);

	lua.bindFunc<module::IntegerMaker>("make",module::BindIntegerMake(&lua));
	lua.bindClassEx<module::IntegerMaker>("new_int");

	lua.bindFunc<module::FloatMaker>("make",module::BindFloatMake(&lua));
	lua.bindClassEx<module::FloatMaker>("new_float");

	lua.cleanUnusedResource<module::IntegerWrapper>();
	lua.cleanUnusedResource<module::IntegerMaker>();
	lua.cleanUnusedResource<module::FloatWrapper>();
	lua.cleanUnusedResource<module::FloatMaker>();

	return 1;
}
