#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <toy/ProcArg.hpp>
#include <toy/io/Writer.hpp>
#include "Interface.hpp"
#include "MyType.hpp"
#include "GetPrefix.hpp"

/*
#if defined(TOY_LINUX)
	// For XInitThreads()
	#include <X11/Xlib.h>
#endif
*/

static inline bool IsFileExist(std::string &filename)
{
	#ifdef TOY_WINDOWS
		return boost::filesystem::exists( toy::utf::UTF8ToWChar(filename) );
	#else
		return boost::filesystem::exists( filename );
	#endif
}

static inline bool IsHere(std::string file)
{
	if ( IsFileExist(file) )
	{
		return true;
	}
	return false;
}

static inline std::string CompleteScriptName( const std::string &main_path, const std::string &main_script )
{
	if ( main_path.empty() ) return main_script;
	return main_path + "/" + main_script;
}

static bool GetConfigData( PlayerConfig *config )
{
	Interface    gui(config);

	gui.run();

	return gui.isGetConfig();
}

static void SetLuaEnvPath(MainLuaState *lua, const std::string &path,const std::string &name, lua::Table &table)
{
	if ( ! path.empty() )
	{
		lua->path( path );
		table[name] = path;
	}
}

static void InitLuaEnvironment( const PlayerConfig &config, MainLuaState *lua )
{
	lua::Table    table;

	SetLuaEnvPath( lua, config.main_path,   "project_path" , table);
	SetLuaEnvPath( lua, config.search_path, "resource_path", table);

	lua->setGlobal( GetConstPrefixPrivate() + "SYSTEM_MESSAGE", table );
}

static bool GetReady( const toy::ProcArg &, MainLuaState *lua, std::string *script )
{
	PlayerConfig   config;

	if ( ! GetConfigData( &config ) )
	{
		return true;
	}

	InitLuaEnvironment(config,lua);
	*script = CompleteScriptName( config.main_path, config.main_script );

	return false;
}

static int main2(int argc, char* argv[])
{
	MainLuaState   lua;
	std::string    script;

	{
		toy::ProcArg     arg(argc,argv,"-","--");

		if ( GetReady(arg,&lua,&script) )
		{
			return EXIT_SUCCESS;
		}
	}

	if ( false == IsHere( script ) )
	{
		toy::Logger<<"Script file \""<<script<<"\" not find."<<toy::NewLine;
		return EXIT_FAILURE;
	}

	#ifdef TOY_WINDOWS
		if ( toy::utf::IsUtf8(script) )
		{
			toy::Logger<<"Not support file name:"<<script<<toy::NewLine;
			toy::Logger<<"Lua can't take unicode name."<<toy::NewLine;
		}
	#endif

	if( false == lua.runScriptFile(script) )
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static void CallBackExit(int signal)
{
	std::string   str;

	switch ( signal )
	{
		case SIGINT:
			str = "SIGINT";
			break;
		#ifndef TOY_WINDOWS
		case SIGSTOP:
			str = "SIGINT";
			break;
		case SIGQUIT:
			str = "SIGINT";
			break;
		#endif
		case SIGTERM:
			str = "SIGINT";
			break;
		default:
			str = "unknown ID";
	}

	toy::Logger<<"std::signal ID:"<<signal<<":"<<str<<toy::NewLine;
}

int main(int argc, char* argv[])
{
	/*
	#if defined(TOY_LINUX)
		XInitThreads();
	#endif
	*/

	std::signal(SIGINT,  &CallBackExit);
	#ifndef TOY_WINDOWS
	std::signal(SIGSTOP, &CallBackExit);
	std::signal(SIGQUIT, &CallBackExit);
	#endif
	std::signal(SIGTERM, &CallBackExit);

	int result = EXIT_FAILURE;

	try
	{
		result = main2(argc,argv);
	}
	catch ( std::exception &e )
	{
		toy::Log(e);
	}

	return result;
}
