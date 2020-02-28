#include <luapp.hpp>
#include <toy/Standard.hpp>
#include <toy/Exception.hpp>
#include <toy/math/SafeInt.hpp>
#include <boost/regex.hpp>

namespace toy{
namespace luamodule{
namespace regex{

class StackGuard
{
	public:

		StackGuard(lua::NativeState h,int stackSize):_size(stackSize),_handle(h)
		{
			;
		}

		~StackGuard()
		{
			lua::Pop(_handle,_size);
		}

		void add(int num)
		{
			_size += num;
		}

		void del(int num)
		{
			if ( num>_size )
			{
				toy::Oops(TOY_MARK);
				num = _size;
			}

			_size -= num;
		}

	private:

		int               _size;
		lua::NativeState  _handle;
};

/*
void Search(boost::regex& re,const std::string& input)
{
	boost::match_results<std::string::const_iterator>     data;
	boost::match_flag_type flags = boost::match_default;

	std::string::const_iterator   start = input.begin();
	std::string::const_iterator   end   = input.end();

	while (boost::regex_search(start,end,data,re,flags))
	{
		std::string::difference_type length   = data.length();
		std::string::difference_type position = data.position();
		start += position + length;
	}
}
*/

static int Search(lua::NativeState L)
{
	lua::Bool    result = false;

	{
		StackGuard   stackGuard(L,3);
		lua::Str     strReg;
		lua::Str     str;

		lua::CheckVarFromLua(L,&strReg,-3);
		lua::CheckVarFromLua(L,&str,-2);

		boost::smatch    mat;
		boost::regex     reg( strReg );

		if ( boost::regex_search( str , mat, reg) )
		{
			lua::Int    index  = -1;
			lua::Int    length = 0;

			toy::math::SafeInt(&index, mat.position(),TOY_MARK);
			toy::math::SafeInt(&length,mat.length(),  TOY_MARK);

			if ( lua::IsType<lua::Func>(L,-1) )
			{
				for ( size_t i = 0; i < mat.size(); ++i )
				{
					if ( mat[i].matched )
					{
						lua::PushValue(L,-1); stackGuard.add(1);
						lua::PushVarToLua( L, lua::Str(mat[i].first,mat[i].second) ); stackGuard.add(1);
						lua::PushVarToLua( L, index ); stackGuard.add(1);
						lua::PushVarToLua( L, length ); stackGuard.add(1);
						lua::PCall(L,3,0,0);
						stackGuard.del(4);
					}
				}
			}
			else
			{
				throw toy::Exception(TOY_MARK);
			}

			result = true;
		}
	}

	lua::PushVarToLua( L, result );

	return 1;
}

static int RecurSearch(lua::NativeState L)
{
	lua::Bool   result = false;

	{
		StackGuard   stackGuard(L,3);

		lua::Str    s_reg;
		lua::Str    str;

		lua::CheckVarFromLua(L,&s_reg,-3);
		lua::CheckVarFromLua(L,&str,-2);

		boost::regex     reg( s_reg );

		boost::sregex_token_iterator   iter(str.begin(), str.end(), reg, 0);
		boost::sregex_token_iterator   end;

		if ( iter != end ) result = true;

		if ( lua::IsType<lua::Func>(L,-1) )
		{
			for( ; iter != end; ++iter )
			{
				lua::PushValue(L,-1);                                       stackGuard.add(1);
				lua::PushVarToLua( L, lua::Str(iter->first,iter->second) ); stackGuard.add(1);
				lua::PCall(L,1,0,0);
				stackGuard.del(2);
			}
		}
		else
		{
			throw toy::Exception(TOY_MARK);
		}
	}

	lua::PushVarToLua( L, result );

	return 1;
}

static int RecurSearchPartial(lua::NativeState L)
{
	lua::Bool   result = false;

	{
		StackGuard  stackGuard(L,3);

		if ( ! lua::IsType<lua::Func>(L,-1) )
		{
			throw toy::Exception(TOY_MARK);
		}

		lua::Int    index  = -1;
		lua::Int    length = 0;
		lua::Str    strReg;
		lua::Str    str;

		lua::CheckVarFromLua(L,&strReg,-3);
		lua::CheckVarFromLua(L,&str,-2);

		boost::smatch    mat;
		boost::regex     reg( strReg );

		auto  begin = str.begin();
		auto  end   = str.end();

		for ( ; ; )
		{
			if ( boost::regex_search( std::string::const_iterator(begin), std::string::const_iterator(end) , mat, reg, boost::match_partial ) )
			{
				toy::math::SafeInt(&index, mat.position(),TOY_MARK);
				toy::math::SafeInt(&length,mat.length(),  TOY_MARK);

				result = true;

			//	for ( size_t i = 0; i < mat.size(); ++i )
				int  i = 0;
				{
					if ( mat[i].matched )
					{
						lua::PushValue(L,-1);                                         stackGuard.add(1);
						lua::PushVarToLua( L, lua::Str(mat[i].first,mat[i].second) ); stackGuard.add(1);
						lua::PushVarToLua( L, static_cast<lua::Bool>(true) );         stackGuard.add(1);
						lua::PushVarToLua( L, index );                                stackGuard.add(1);
						lua::PushVarToLua( L, length );                               stackGuard.add(1);
						lua::PCall(L,4,0,0);
						stackGuard.del(5);
					}
					else
					{
						lua::PushValue(L,-1);                                         stackGuard.add(1);
						lua::PushVarToLua( L, lua::Str(mat[i].first,mat[i].second) ); stackGuard.add(1);
						lua::PushVarToLua( L, static_cast<lua::Bool>(false));         stackGuard.add(1);
						lua::PushVarToLua( L, index );                                stackGuard.add(1);
						lua::PushVarToLua( L, length );                               stackGuard.add(1);
						lua::PCall(L,4,0,0);
						stackGuard.del(5);
						break;
					}
				}

				begin = begin + index + length;
			}
			else
			{
				break;
			}
		}
	}

	lua::PushVarToLua( L, result );

	return 1;
}

static int IsMatch(lua::NativeState L)
{
	lua::Bool   result = false;

	{
		lua::Str    strReg;
		lua::Str    str;

		{
			StackGuard   stackGuard(L,2);
			lua::CheckVarFromLua(L,&strReg,-2);
			lua::CheckVarFromLua(L,&str,-1);
		}

		boost::cmatch    mat;
		boost::regex     reg( strReg );

		if ( boost::regex_match( str.c_str() , mat, reg) )
		{
			result = true;
		}
	}

	lua::PushVarToLua( L, result );

	return 1;
}

#if TOY_OPTION_ENABLE_BETA_API
static int Match(lua::NativeState L)
{
	lua::Bool   result = false;

	{
		StackGuard   stackGuard(L,3);
		lua::Str     strReg;
		lua::Str     str;

		lua::CheckVarFromLua(L,&strReg,-3);
		lua::CheckVarFromLua(L,&str,-2);

		boost::cmatch    mat;
		boost::regex     reg( strReg );

		if ( boost::regex_match( str.c_str() , mat, reg) )
		{
			if ( lua::IsType<lua::Func>(L,-1) )
			{
				auto it = mat.begin();
				{
					lua::PushValue(L,-1); stackGuard.add(1);
					lua::PushVarToLua( L, lua::Str(it->first,it->second) ); stackGuard.add(1);
					lua::PCall(L,1,0,0);
					stackGuard.del(2);
				}
			}
			else
			{
				throw toy::Exception(TOY_MARK);
			}

			result = true;
		}
	}

	lua::PushVarToLua( L, result );

	return 1;
}
#endif

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_regex(lua::NativeState L)
{
	lua::State<>    lua(L);

	lua.setFunc( "is_match",              ::toy::luamodule::regex::IsMatch );
	lua.setFunc( "search",                ::toy::luamodule::regex::Search );
	lua.setFunc( "recur_search",          ::toy::luamodule::regex::RecurSearch );
	lua.setFunc( "recur_search_partial",  ::toy::luamodule::regex::RecurSearchPartial );
	#if TOY_OPTION_ENABLE_BETA_API
	lua.setFunc( "match",                 ::toy::luamodule::regex::Match );
	#endif

	return 1;
}
