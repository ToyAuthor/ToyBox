#include <vector>
#include <string>
#include <luapp.hpp>
#include <toy/math/SafeInt.hpp>
#include <toy/parser/Analyzer.hpp>

namespace toy{
namespace luamodule{
namespace string{

class AnalyzerWrapper
{
	public:

		AnalyzerWrapper()
		{
			;
		}

		~AnalyzerWrapper()
		{
			;
		}

		bool next(std::string *str)
		{
			return _core.nextWord(str);
		}

		void pushConfig(lua::Table tt)
		{
			auto config = std::make_shared<toy::parser::AnalyzerConfig>();

			lua::Var  key;
			lua::Var  value;
			lua::Var* var = &(tt>>"ignore");

			if ( lua::VarType<lua::Table>(*var) )
			{
				auto it = lua::VarPtr<lua::Table>(var)->getBegin();

				for ( ; ! it.isEnd() ; it++ )
				{
					it.getKeyValue(&key, &value);

					auto str = lua::VarPtr<lua::Str>(&value);

					if ( str )
					{
						config->ignoreCharList.push((*str)[0]);
					}
				}
			}

			var = &(tt>>"break_char");

			if ( lua::VarType<lua::Table>(*var) )
			{
				auto it = lua::VarPtr<lua::Table>(var)->getBegin();

				for ( ; ! it.isEnd() ; it++ )
				{
					it.getKeyValue(&key, &value);

					auto str = lua::VarPtr<lua::Str>(&value);

					switch ( str->size() )
					{
						case 1:
							config->breakCharList.push((*str)[0]);
							break;
						case 2:
							config->breakDoubleCharList.push(toy::parser::AnalyzerConfig::DChar((*str)[0],(*str)[1]));
							break;
						case 3:
							config->breakTripleCharList.push(toy::parser::AnalyzerConfig::TChar((*str)[0],(*str)[1],(*str)[2]));
							break;
						default:
							toy::Oops(TOY_MARK);
					}
				}
			}

			_core.pushConfig(config);
		}

		void popConfig(lua::Int num)
		{
			_core.popConfig(toy::math::SafeInt<int>(num,TOY_MARK));
		}

		void load(lua::Str str)
		{
			_core.loadString(str,toy::RIGHTWARD);
		}

		void load2(lua::Str str,lua::Var optionStr)
		{
			toy::Option  option = toy::RIGHTWARD;

			auto ptr = lua::VarPtr<lua::Str>(&optionStr);

			if ( ptr )
			{
				lua::Str &opt = *ptr;

				if ( opt=="right" )
				{
					;
				}
				else if ( opt=="left" )
				{
					option = toy::LEFTWARD;
				}
				else
				{
					toy::Oops(TOY_MARK);
				}
			}

			_core.loadString(str,option);
		}

	private:

		toy::parser::Analyzer     _core;
};

static int AnalyzerNextWord(lua::NativeState L)
{
	                          // ... [T]
	lua::_PushCoreKey(L);     // ... [T] [key]
	lua::GetTable(L, -2);     // ... [T] [UD]
	AnalyzerWrapper* obj = static_cast<AnalyzerWrapper*>(lua::CheckUserData(L, -1, lua::CreateBindingCoreName<AnalyzerWrapper>()));
	lua::Pop(L, 2);           // ...

	std::string  result;

	if ( obj->next(&result) )
	{
		lua::Str  str;
		str.swap(result);
		lua::PushVarToLua(L,str);
	}
	else
	{
		lua::PushNil(L);
	}

	return 1;
}

static inline bool IsMatch(const lua::Str &key,const lua::Str &str,uint32_t index)
{
	for ( uint32_t i=1 ; i<key.size() ; i++ )
	{
		if ( key[i]!=str[index+i] )
		{
			return false;
		}
	}

	return true;
}

static inline lua::Int FindItOut(const lua::Str &key,const lua::Str &str)
{
	if ( key.size()==0 ) return -1;
	if ( str.size() < key.size() ) return -1;

	uint32_t   size = str.size()-key.size()+1;

	for ( uint32_t i=0 ; i<size ; i++ )
	{
		if ( str[i]==key[0] )
		{
			if ( IsMatch(key,str,i) )
			{
				return i;
			}
		}
	}

	return -1;  // Nothing matched.
}

static int Find(lua::NativeState L)
{
	lua::Str    key;
	lua::Str    str;
	lua::PullArgs( L, key, str );

	auto   result = FindItOut(key,str);

	if ( result<0 )
	{
		lua::PushVarToLua( L, lua::Nil() );
	}
	else
	{
		lua::PushVarToLua( L, result );
	}

	return 1;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_split(lua::NativeState L)
{
	namespace module = ::toy::luamodule::string;

	lua::State<>    lua(L);

	lua.setFunc( "find",             module::Find );

	lua.bindMethod( "load", &module::AnalyzerWrapper::load );
	lua.bindMethod( "load_ex", &module::AnalyzerWrapper::load2 );
	lua.bindMethod( "push_config", &module::AnalyzerWrapper::pushConfig );
	lua.bindMethod( "pop_config", &module::AnalyzerWrapper::popConfig );
	lua.bindFunc<module::AnalyzerWrapper>("next",&module::AnalyzerNextWord);
	lua.bindClassEx<module::AnalyzerWrapper>("create_splitter");

	lua.cleanUnusedResource<module::AnalyzerWrapper>();

	return 1;
}
