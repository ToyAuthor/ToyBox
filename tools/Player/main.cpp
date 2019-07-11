#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <toy/ProcArg.hpp>
#include <toy/io/Writer.hpp>
#include "MyType.hpp"
#include "PrintInfo.hpp"
#include "GetPrefix.hpp"

#define TOYBOX_PLAYER_CONFIG_NAME "default-config.lua"
#define TOYBOX_PLAYER_DEFAULT_MAIN_SCRIPT_NAME "main.lua"

static inline bool IsFileExist(std::string &filename)
{
	#ifdef TOY_WINDOWS
		return boost::filesystem::exists( toy::utf::UTF8ToWChar(filename) );
	#else
		return boost::filesystem::exists( filename );
	#endif
}

static inline void RemoveFile(std::string &filename)
{
	#ifdef TOY_WINDOWS
		boost::filesystem::remove( toy::utf::UTF8ToWChar(filename) );
	#else
		boost::filesystem::remove( filename );
	#endif
}

// I must separate path and script name. They can't be a single string.
struct PlayerConfig
{
	std::string    main_path;                // It's a path of main script, and a search path too.
	std::string    search_path;              // It's a search path for searching common scripts or resource ...etc.
	std::string    main_script = TOYBOX_PLAYER_DEFAULT_MAIN_SCRIPT_NAME;
};

using toy::Logger;

static inline void UpBlank()
{
	Logger<<toy::NewLine;
}

static inline void DownBlank()
{
	#ifndef TOY_WINDOWS
	Logger<<toy::NewLine;
	#endif
}

static void ResetDefaultConfig()
{
	std::string   config = TOYBOX_PLAYER_CONFIG_NAME;

	std::string   text;
	text += R"===(
-- This config file is created by player.
-- Type "./player --reset" to reset config to default content.

-- Path of the project. (Where you put down main script and resource ... etc)
main_path = "."
--main_path = "/opt/configs"

-- Path of the other modules. It's optional.
--search_path = "."
--search_path = "d:configs/libs"

-- The name of main script. Now loading itself to show a simple demo.
script = ")===" + config + R"===("

print("This message just for demo")
)===";

	if ( IsFileExist( config ) )
	{
		RemoveFile( config );
	}

	toy::io::Writer<>   writer;
	writer.open(config);
	writer.print(text);
}

static inline int IsHere(std::string file)
{
	if ( IsFileExist(file) )
	{
		return 1;
	}
	return 0;
}

static inline std::string CompleteScriptName( const std::string &main_path, const std::string &main_script )
{
	if ( main_path.empty() ) return main_script;
	return main_path + "/" + main_script;
}

static void ReadConfig( const std::string &configFile, PlayerConfig *config )
{
	lua::State<>   reader;

	#if !TOY_OPTION_RELEASE
		// Binary release doesn't need it. That's why resource path only exist in debug mode.
		reader.setGlobal(GetConstPrefix()+"RESOURCE_PATH_FOR_DEMO",std::string(TOY_RESOURCE_PATH));
	#endif

	reader.runScriptFile(configFile);
	lua::Var  temp;
	reader.getGlobal("main_path",&temp);   lua::CopyVar<lua::Str>(config->main_path,temp);
	reader.getGlobal("script",&temp);      lua::CopyVar<lua::Str>(config->main_script,temp);
//	reader.getGlobal("search_path",&temp); lua::CopyVar<lua::Str>(config->search_path,temp);
	reader.getGlobal("search_path",&temp); lua::TryCopyVar<lua::Str>(config->search_path,temp);
}

static bool GetConfigData( PlayerConfig *config, const std::string &configFile )
{
	if ( IsHere(configFile) )
	{
		#ifdef TOY_WINDOWS
			if ( toy::utf::IsUtf8(configFile) )
			{
				Logger<<"Not support file name:"<<configFile<<toy::NewLine;
				Logger<<"Lua can't take unicode name."<<toy::NewLine;
			}
		#endif

		ReadConfig(configFile,config);

		return true;
	}

	if ( IsHere(TOYBOX_PLAYER_DEFAULT_MAIN_SCRIPT_NAME) )
	{
		return true;
	}

	Logger<<"Configuration file \""<<configFile<<"\" not find."<<toy::NewLine;

	return false;
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

static bool GetReady( const toy::ProcArg &arg, MainLuaState *lua, std::string *script )
{
	PlayerConfig   config;

	if ( arg.tags().size() > 0 )
	{
		std::shared_ptr<const std::vector<std::string>>   ptr = nullptr;

		ptr = arg[""];
		if ( ptr )
		{
			if ( !GetConfigData( &config, ptr->front() ) )
			{
				throw toy::Exception(TOY_MARK);
			}

			InitLuaEnvironment(config,lua);
			*script = CompleteScriptName( config.main_path, config.main_script );

			return false;
		}
		if ( arg["--help"]      || arg["-h"] ) { UpBlank(); PrintHelp(       arg); DownBlank(); return true; }
		if ( arg["--version"]   || arg["-v"] ) {            PrintVersion(    arg);              return true; }
		if ( arg["--example"]   || arg["-e"] ) { UpBlank(); PrintExample(    arg); DownBlank(); return true; }
		if ( arg["--copyright"] || arg["-c"] ) { UpBlank(); PrintCopyright(  arg); DownBlank(); return true; }
		if ( arg["--info"]      || arg["-i"] ) { UpBlank(); PrintInformation(arg); DownBlank(); return true; }
		if ( arg["--reset"]     || arg["-r"] )
		{
			ResetDefaultConfig();
			return true;
		}
		ptr = arg["--project"];
		if ( ptr && ptr->size()>0 )
		{
			config.main_path = ptr->front();

			auto temp = arg["--main-script"];

			if ( temp && temp->size()>0 )
			{
				config.main_script = temp->front();
			}
			else
			{
				config.main_script = TOYBOX_PLAYER_DEFAULT_MAIN_SCRIPT_NAME;
			}

			InitLuaEnvironment(config,lua);
			*script = CompleteScriptName( config.main_path, config.main_script );

			return false;
		}
		if ( (arg.tags().size()-((arg[""]==nullptr)?0:1))>0 )
		{
			UpBlank();
			PrintPrompt(arg);
			DownBlank();
			return true;
		}
	}

	if ( !GetConfigData( &config, std::string(TOYBOX_PLAYER_CONFIG_NAME) ) )
	{
		throw toy::Exception(TOY_MARK);
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
		Logger<<"Script file \""<<script<<"\" not find."<<toy::NewLine;
		return EXIT_FAILURE;
	}


	#ifdef TOY_WINDOWS
		if ( toy::utf::IsUtf8(script) )
		{
			Logger<<"Not support file name:"<<script<<toy::NewLine;
			Logger<<"Lua can't take unicode name."<<toy::NewLine;
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

	Logger<<"std::signal ID:"<<signal<<":"<<str<<toy::NewLine;
}

int main(int argc, char* argv[])
{
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

#undef TOYBOX_PLAYER_CONFIG_NAME
#undef TOYBOX_PLAYER_DEFAULT_MAIN_SCRIPT_NAME
