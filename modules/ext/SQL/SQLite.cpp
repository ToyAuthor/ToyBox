#include <string>
#include <luapp.hpp>
#include <toy/Environment.hpp>
#include <toy/Exception.hpp>
#include <toy/Log.hpp>
#include <sqlite3.h>

namespace toy{
namespace luamodule{
namespace sql{

class DataBaseWrapper
{
	public:

		DataBaseWrapper(const std::string &filename)
		{
			if ( SQLITE_OK != sqlite3_open(filename.c_str(), &(_handle)) )
			{
				toy::Logger<<sqlite3_errmsg(_handle)<<toy::NewLine;
				throw toy::Exception(TOY_MARK);
			}
		}

		~DataBaseWrapper()
		{
			sqlite3_close(_handle);
		}

		void setErrorMsg(const std::string &str)
		{
			_errorMsg = str;
		}

		lua::Str getErrorMsg()
		{
			return _errorMsg;
		}

		sqlite3* handle()
		{
			return _handle;
		}

		void fuss(bool flag)
		{
			_fuss = flag;
		}

		lua::Bool fuss()
		{
			return _fuss;
		}

	private:

		sqlite3*       _handle = nullptr;
		std::string    _errorMsg = "";
		bool           _fuss = true;
};

static lua::Str                                          ClassNameUD;
static std::function<void(std::string,std::string)>      CommandCallback = {};

static int Device_Destructor(lua::NativeState L)
{
	auto obj = static_cast<DataBaseWrapper*>(lua::CheckUserData(L, -1, ClassNameUD));
	obj->~DataBaseWrapper();

	return 0;
}

static int SQLiteCallback(void *root, int argc, char **argv, char **azColName)
{
	if ( root==nullptr ) return 0;

	auto func = (std::function<void(std::string,std::string)>*)root;

	for ( int i=0; i<argc; i++ )
	{
		(*func)(azColName[i],(const char*)(argv[i] ? argv[i] : "NULL"));
	}

	return 0;
}

// bool func(cmd,closure(str,str))
static int Device_SendCommand(lua::NativeState L)
{
	//                                             // ... [T] [command] [closure(may be doesn't exist)]
	auto callbackFunc = static_cast<void*>(&CommandCallback);

	if ( ! lua::IsType<lua::Func>(L,-1) )
	{
		//                                            ... [T] [command]
		callbackFunc = nullptr;
		lua::PushInteger(L, 0);                    // ... [T] [command] [integer(pretend it's closure)]
	}

	//                                                ... [T] [command] [closure]
	lua::_PushCoreKey(L);                          // ... [T] [command] [closure] [key]
	lua::GetTable(L, -4);                          // ... [T] [command] [closure] [user data]

	auto obj = static_cast<DataBaseWrapper*>(lua::CheckUserData(L, -1, ClassNameUD));

	lua::Pop(L, 1);                                // ... [T] [command] [closure]
	lua::Str     command;
	lua::Bool    result = true;
	lua::CheckVarFromLua(L,&command,-2);

	char *errMsg = nullptr;

	if( SQLITE_OK != sqlite3_exec(obj->handle(), command.c_str(), SQLiteCallback, callbackFunc, &errMsg) )
	{
		obj->setErrorMsg(errMsg);
		sqlite3_free(errMsg);

		if ( obj->fuss() )
		{
			lua::Pop(L, 3);
			throw toy::Exception(TOY_MARK);
		}

		result = false;
	}

	lua::Pop(L, 3);                                // ...
	lua::PushVarToLua( L, result );                // ... [bool]

	return 1;
}

static int Device_GetErrorMessage(lua::NativeState L)
{
	//                                               ... [T]
	lua::_PushCoreKey(L);                         // ... [T] [key]
	lua::GetTable(L, 1);                          // ... [T] [user data]
	auto obj = static_cast<DataBaseWrapper*>(lua::CheckUserData(L, -1, ClassNameUD));
	lua::Pop(L, 2);                               // ...
	lua::PushVarToLua( L, obj->getErrorMsg() );   // ... [string]
	return 1;
}

static int Device_SetFuss(lua::NativeState L)
{
	//                                               ... [T] [flag(may be doesn't exist)]
	lua::Bool   flag;
	bool        flagExist = false;

	if ( lua::IsType<lua::Bool>(L,-1) )
	{
		flagExist = true;
		lua::PullArgs(L,flag);
	}

	//                                               ... [T]

	lua::_PushCoreKey(L);                         // ... [T] [key]
	lua::GetTable(L, -2);                         // ... [T] [user data]
	auto obj = static_cast<DataBaseWrapper*>(lua::CheckUserData(L, -1, ClassNameUD));
	lua::Pop(L, 2);                               // ...

	if ( flagExist )
	{
		obj->fuss(flag);
	}

	lua::PushVarToLua( L, obj->fuss() );          // ... [bool]

	return 1;
}

static int OpenDevice(lua::NativeState L)
{
	//                                                    ... [database file name]
	lua::Str   filename;
	lua::PullArgs(L,filename);                         // ...

	lua::NewTable(L);                                  // ... [T]
	lua::_PushCoreKey(L);                              // ... [T] [key]

	auto a = (DataBaseWrapper*)lua::NewUserData(L, sizeof(DataBaseWrapper));         // ... [T] [key] [UD]
	new (a) DataBaseWrapper(filename);

	lua::NewMetaTable(L, ClassNameUD);                 // ... [T] [key] [UD] [MT]
	lua::SetMetaTable(L, -2);                          // ... [T] [key] [UD]
	lua::SetTable(L, -3);                              // ... [T]

	lua::PushString(L, "__gc");                        // ... [T] [member func name]
	lua::PushFunction(L, Device_Destructor);           // ... [T] [member func name] [func address]
	lua::SetTable(L, -3);                              // ... [T]

	lua::PushString(L, "cmd");                         // ... [T] [member func name]
	lua::PushFunction(L, Device_SendCommand);          // ... [T] [member func name] [func address]
	lua::SetTable(L, -3);                              // ... [T]

	lua::PushString(L, "error_msg");                   // ... [T] [member func name]
	lua::PushFunction(L, Device_GetErrorMessage);      // ... [T] [member func name] [func address]
	lua::SetTable(L, -3);                              // ... [T]

	lua::PushString(L, "fuss");                        // ... [T] [member func name]
	lua::PushFunction(L, Device_SetFuss);              // ... [T] [member func name] [func address]
	lua::SetTable(L, -3);                              // ... [T]

	return 1;
}

}}}

#ifdef TOY_WINDOWS
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_sql(lua::NativeState L)
{
	namespace module = ::toy::luamodule::sql;

	module::ClassNameUD = lua::CreateBindingCoreName<module::DataBaseWrapper>();

	module::CommandCallback = [L](std::string name,std::string value)
	{
		//                                    ... [T] [command] [closure]
		lua::PushValue(L,-1);              // ... [T] [command] [closure] [closure]
		lua::PushVarToLua( L, name );      // ... [T] [command] [closure] [closure] [name]
		lua::PushVarToLua( L, value );     // ... [T] [command] [closure] [closure] [name] [value]
		lua::PCall(L,2,0,0);               // ... [T] [command] [closure]
	};

	lua::FuncReg   reg;

	reg.add( "open", module::OpenDevice );

	lua::NewModule(L,reg);

	return 1;
}
