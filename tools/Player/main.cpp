#include <cstdio>
#include <cstdlib>
#include <csignal>
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
	text += R"(
-- This config file is created by player.
-- Type "./player --reset" to reset config to default content.

-- Path of the project. (Where you put down main script and resource ... etc)
main_path = "."
--main_path = "/opt/configs"

-- Path of the other modules.
--search_path = "."
--search_path = "d:configs/libs"

-- The name of main script. Now loading itself to show a simple demo.
script = ")" + config + R"("

print("This message just for demo")
)";

	if ( IsFileExist( config ) )
	{
		RemoveFile( config );
	}

	toy::io::Writer<>   writer;
	writer.open(config);
	writer.print(text);
}

static int PrintManual(const SystemArgs &arg)
{
	if ( arg.num > 1 )
	{
		std::string   str = arg[1];

		if ( str=="--help"      || str=="-h" ) { UpBlank(); PrintHelp(       arg); DownBlank(); return (int)1; }
		if ( str=="--version"   || str=="-v" ) {            PrintVersion(    arg);              return (int)1; }
		if ( str=="--example"   || str=="-e" ) { UpBlank(); PrintExample(    arg); DownBlank(); return (int)1; }
		if ( str=="--copyright" || str=="-c" ) { UpBlank(); PrintCopyright(  arg); DownBlank(); return (int)1; }
		if ( str=="--info"      || str=="-i" ) { UpBlank(); PrintInformation(arg); DownBlank(); return (int)1; }

		if ( str=="--comment"   || str=="-co")
		{
			Logger<<"It's not ready yet!"<<toy::NewLine;
			return 1;
		}

		if ( str=="--reset"     || str=="-r" )
		{
			ResetDefaultConfig();
			return 1;
		}

		if ( str.c_str()[0] == '-' )
		{
			UpBlank();
			PrintPrompt(arg);
			DownBlank();
			return 1;
		}
	}

	return 0;      // No message output. User didn't asking for message.
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

static bool ReadConfig( std::string config_file, PlayerConfig *config )
{
	lua::State<>   reader;

	#if !TOY_OPTION_RELEASE
		// Binary release doesn't need it. That's why resource path only exist in debug mode.
		reader.setGlobal(GetPrefix()+"ResourcePathForDemo",std::string(TOY_RESOURCE_PATH));
	#endif

	reader.runScriptFile(config_file);
	lua::Var  a;
	lua::Var  b;
	lua::Var  c;
	reader.getGlobal("main_path",&a);   lua::CopyVar<lua::Str>(config->main_path,a);
	reader.getGlobal("script",&c);      lua::CopyVar<lua::Str>(config->main_script,c);
//	reader.getGlobal("search_path",&b); lua::CopyVar<lua::Str>(config->search_path,b);
	reader.getGlobal("search_path",&b); lua::TryCopyVar<lua::Str>(config->search_path,b);

	auto   name = CompleteScriptName( config->main_path, config->main_script );

	if ( IsHere( name ) )
	{
		return true;
	}

	Logger<<"Script file \""<<name<<"\" not find."<<toy::NewLine;
	Logger<<"Wrong information in config file."<<toy::NewLine;

	return false;
}

static bool GetConfigData( const SystemArgs &arg, PlayerConfig *config )
{
	std::string    config_file(TOYBOX_PLAYER_CONFIG_NAME);

	if ( arg.num>1 )
	{
		config_file = arg[1];
	}

	if ( IsHere(config_file) )
	{
		#ifdef TOY_WINDOWS
			if ( toy::utf::IsUtf8(config_file) )
			{
				Logger<<"Not support file name:"<<config_file<<toy::NewLine;
				Logger<<"Lua can't take unicode name."<<toy::NewLine;
			}
		#endif
		return ReadConfig(config_file,config);
	}

	if ( IsHere(TOYBOX_PLAYER_DEFAULT_MAIN_SCRIPT_NAME) && arg.num==1 )
	{
		return true;
	}

	Logger<<"Configuration file \""<<config_file<<"\" not find."<<toy::NewLine;
	Logger<<"Type \"player.exe --help\" to get more information"<<toy::NewLine;

	return false;
}

static void SetLuaEnvPath(MainLuaState *lua, std::string path, std::string globalName)
{
	if ( ! path.empty() )
	{
		lua->path( path );
		lua->setGlobal( GetPrefix() + globalName, path );
	}
}

static void InitLuaEnvironment( const PlayerConfig &config, MainLuaState *lua )
{
	SetLuaEnvPath( lua, config.main_path,   "ProjectPath" );
	SetLuaEnvPath( lua, config.search_path, "ResourcePath" );
}

static std::string GetReady( const SystemArgs &arg, MainLuaState *lua )
{
	PlayerConfig   config;

	if ( !GetConfigData( arg, &config ) )
	{
		throw std::runtime_error("Config file can't provide message to player");
	}

	InitLuaEnvironment(config,lua);

	return CompleteScriptName( config.main_path, config.main_script );
}

static int main2(int argc, char* argv[])
{
	SystemArgs     arg(argc,argv);

	if ( PrintManual(arg) )
	{
		return EXIT_SUCCESS;
	}

	MainLuaState    lua;

	auto  script = GetReady(arg,&lua);

	#ifdef TOY_WINDOWS
		if ( toy::utf::IsUtf8(script) )
		{
			Logger<<"Not support file name:"<<script<<toy::NewLine;
			Logger<<"Lua can't take unicode name."<<toy::NewLine;
		}
	#endif

	if( ! lua.runScriptFile(script) )
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
