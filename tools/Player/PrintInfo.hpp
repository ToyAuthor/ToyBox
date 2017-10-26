
#pragma once

#include <sstream>
#include <toy/Environment.hpp>
#include <toy/Version.hpp>
#include "SystemArgs.hpp"

#ifdef TOY_TEXT
	#error "Need a new name"
#endif

#ifdef TOY_WINDOWS
	#define TOY_TEXT(x) L ## x
#else
	#define TOY_TEXT(x) x
#endif

using toy::Logger;

inline void PrintOptionList_English()
{
	toy::Log(TOY_TEXT("    player.exe               # Read default-config.lua in current directory\n"));
	toy::Log(TOY_TEXT("    player.exe --copyright   # Show copyright of ToyBox\n"));
	toy::Log(TOY_TEXT("    player.exe --example     # Example for reading config file\n"));
	toy::Log(TOY_TEXT("    player.exe --help        # English\n"));
	toy::Log(TOY_TEXT("    player.exe --help -sc    # 简体中文\n"));
	toy::Log(TOY_TEXT("    player.exe --help -tc    # 繁體中文\n"));
	toy::Log(TOY_TEXT("    player.exe --info        # Get more information\n"));
	toy::Log(TOY_TEXT("    player.exe --version     # Show version of ToyBox\n"));
	toy::Log(TOY_TEXT("    player.exe --reset       # Reset default-config.lua\n"));
}

inline void PrintOptionList_TraditionalChinese()
{
	toy::Log(TOY_TEXT("    player.exe                   # 讀取當前資料夾的default-config.lua\n"));
	toy::Log(TOY_TEXT("    player.exe --copyright -tc   # 顯示版權聲明\n"));
	toy::Log(TOY_TEXT("    player.exe --example -tc     # 顯示讀取設定檔的使用範例\n"));
	toy::Log(TOY_TEXT("    player.exe --help -tc        # 顯示使用說明\n"));
	toy::Log(TOY_TEXT("    player.exe --info -tc        # 顯示程式內部資訊\n"));
	toy::Log(TOY_TEXT("    player.exe --version -tc     # 顯示版本資訊\n"));
	toy::Log(TOY_TEXT("    player.exe --reset -tc       # 將預設讀取的設定檔恢復回預設內容\n"));
}

inline void PrintOptionList_SimplifiedChinese()
{
	toy::Log(TOY_TEXT("    player.exe                   # 读取当前资料夹的default-config.lua\n"));
	toy::Log(TOY_TEXT("    player.exe --copyright -sc   # 显示版权声明\n"));
	toy::Log(TOY_TEXT("    player.exe --example -sc     # 显示读取设定档的使用范例\n"));
	toy::Log(TOY_TEXT("    player.exe --help -sc        # 显示使用说明\n"));
	toy::Log(TOY_TEXT("    player.exe --info -tc        # 显示软件内部资讯\n"));
	toy::Log(TOY_TEXT("    player.exe --version -sc     # 显示版本资讯\n"));
	toy::Log(TOY_TEXT("    player.exe --reset -sc       # 将预设读取的设定档恢复回预设内容\n"));
}

inline void PrintHelp_English()
{
	toy::Log(TOY_TEXT("Usage:\n"));
	PrintOptionList_English();
}

inline void PrintHelp_TraditionalChinese()
{
	toy::Log(TOY_TEXT("使用說明:\n"));
	PrintOptionList_TraditionalChinese();
}

inline void PrintHelp_SimplifiedChinese()
{
	toy::Log(TOY_TEXT("使用说明:\n"));
	PrintOptionList_SimplifiedChinese();
}

inline void PrintHelp(const SystemArgs &arg)
{
	if(arg.num>2)
	{
		std::string     param=arg[2];

		if(param=="-tc") { PrintHelp_TraditionalChinese();  return; }
		if(param=="-sc") { PrintHelp_SimplifiedChinese();   return; }
	}

	PrintHelp_English();
}

inline std::string PrintVersion_GetVersion()
{
	std::stringstream   stream;

	stream << toy::GetMajorVersion() << "." << toy::GetMinorVersion() << "." << toy::GetPatchVersion();

	std::string  str;
	stream >> str;

	#if !TOY_OPTION_RELEASE
	str += ".x debug mode";
	#endif

	return str;
}

inline void PrintVersion_English()
{
	/*
	 * The symbol "%s" only work for ansi key code.
	 * And the symbol "%ls" only work for wide character.
	 * So toy::Logger is the only one choice.
	 */
	Logger<<TOY_TEXT("ToyBox version ")<<PrintVersion_GetVersion()<<toy::NextLine;
}

inline void PrintVersion_TraditionalChinese()
{
	Logger<<TOY_TEXT("ToyBox 當前版本為 ")<<PrintVersion_GetVersion()<<toy::NextLine;
}

inline void PrintVersion_SimplifiedChinese()
{
	Logger<<TOY_TEXT("ToyBox 当前版本为 ")<<PrintVersion_GetVersion()<<toy::NextLine;
}

inline void PrintVersion(const SystemArgs &arg)
{
	if(arg.num>2)
	{
		std::string     param=arg[2];

		if(param=="-tc") { PrintVersion_TraditionalChinese();  return; }
		if(param=="-sc") { PrintVersion_SimplifiedChinese();   return; }
	}

	PrintVersion_English();
}

inline void PrintPrompt(const SystemArgs &arg)
{
	std::string     cmd=arg[1];

	if(arg.num>2)
	{
		std::string     param=arg[2];

		if(param=="-tc")
		{
			Logger<<TOY_TEXT("沒有")<<cmd<<TOY_TEXT("這個指令，只有提供下列選項:")<<toy::NextLine<<toy::NextLine;
			PrintOptionList_TraditionalChinese();
			return;
		}
		if(param=="-sc")
		{
			Logger<<TOY_TEXT("没有")<<cmd<<TOY_TEXT("这个指令，只有提供下列选项:")<<toy::NextLine<<toy::NextLine;
			PrintOptionList_SimplifiedChinese();
			return;
		}
	}

	Logger<<TOY_TEXT("Command ")<<cmd<<TOY_TEXT(" doesn't exist! You just only have following options:")<<toy::NextLine<<toy::NextLine;
	PrintOptionList_English();
}

inline void PrintExample_English()
{
	toy::Log(TOY_TEXT("For examples:\n"));
	toy::Log(TOY_TEXT("    player.exe d:configs/default-config.lua    # General usage\n"));
	toy::Log(TOY_TEXT("    player.exe                                 # Read \"default-config.lua\" in the working directory\n"));
}

inline void PrintExample_TraditionalChinese()
{
	toy::Log(TOY_TEXT("使用範例:\n"));
	toy::Log(TOY_TEXT("    player.exe d:configs/default-config.lua    # 一般用法\n"));
	toy::Log(TOY_TEXT("    player.exe                                 # 讀當前資料夾的\"default-config.lua\"設定檔\n"));
}

inline void PrintExample_SimplifiedChinese()
{
	toy::Log(TOY_TEXT("使用范例:\n"));
	toy::Log(TOY_TEXT("    player.exe d:configs/default-config.lua    # 一般用法\n"));
	toy::Log(TOY_TEXT("    player.exe                                 # 读当前资料夹的\"default-config.lua\"设定档\n"));
}

inline void PrintExample(const SystemArgs &arg)
{
	if(arg.num>2)
	{
		std::string     param=arg[2];

		if(param=="-tc")   { PrintExample_TraditionalChinese();  return; }
		if(param=="-sc")   { PrintExample_SimplifiedChinese();   return; }
	}

	PrintExample_English();
}

inline void PrintCopyright_English()
{
	toy::Log(TOY_TEXT("    Copyright (c) 2014-2016 ToyAuthor\n"));
	toy::Log(TOY_TEXT("\n"));

	toy::Log(TOY_TEXT("    This software is a part of ToyBox.\n"));
	toy::Log(TOY_TEXT("    ToyBox is release into public domain.\n"));
	toy::Log(TOY_TEXT("    Be careful, those third party libraries have their own license.\n"));
	toy::Log(TOY_TEXT("    The font files have their own license too.\n"));
	toy::Log(TOY_TEXT("    The others resources are belong to public domain.(scripts,images...etc)\n"));
	toy::Log(TOY_TEXT("    I recommand you keep the license folder.\n"));
}

inline void PrintCopyright_TraditionalChinese()
{
	toy::Log(TOY_TEXT("    Copyright (c) 2014-2016 ToyAuthor\n"));
	toy::Log(TOY_TEXT("\n"));

	toy::Log(TOY_TEXT("    本程式屬於 ToyBox 的一部份\n"));
	toy::Log(TOY_TEXT("    ToyBox 本身是以 Public Domain 形式發佈的軟體\n"));
	toy::Log(TOY_TEXT("    但是要注意內部所引用的第三方工具有著各自的授權條款\n"));
	toy::Log(TOY_TEXT("    至於腳本文字檔與圖片皆沒有保留著作權或者附帶授權條款\n"));
	toy::Log(TOY_TEXT("    可以自由使用\n"));
	toy::Log(TOY_TEXT("    建議別刪掉用來做版權聲明的 license 資料夾\n"));
}

inline void PrintCopyright_SimplifiedChinese()
{
	toy::Log(TOY_TEXT("    Copyright (c) 2014-2016 ToyAuthor\n"));
	toy::Log(TOY_TEXT("\n"));

	toy::Log(TOY_TEXT("    本软件属于 ToyBox 的一部份\n"));
	toy::Log(TOY_TEXT("    ToyBox 本身是以 Public Domain 形式发布的软件\n"));
	toy::Log(TOY_TEXT("    但是要注意内部所引用的第三方工具有着各自的许可协议\n"));
	toy::Log(TOY_TEXT("    至于脚本文字档与图片皆没有附带着作权以及许可协议\n"));
	toy::Log(TOY_TEXT("    可以自由使用\n"));
	toy::Log(TOY_TEXT("    建议别删掉用来做版权声明的 license 资料夹\n"));
}

inline void PrintCopyright(const SystemArgs &arg)
{
	if(arg.num>2)
	{
		std::string     param=arg[2];

		if(param=="-tc")   { PrintCopyright_TraditionalChinese();  return; }
		if(param=="-sc")   { PrintCopyright_SimplifiedChinese();   return; }
	}

	PrintCopyright_English();
}

inline std::string PrintInformation_GetPlatform()
{
	#if   defined(TOY_ANDROID)
		std::string os = "Android";
	#elif defined(TOY_LINUX)
		std::string os = "Linux";
	#elif defined(TOY_MAC)
		std::string os = "Mac OS";
	#elif defined(TOY_WINDOWS)
		std::string os = "Windows";
	#elif defined(TOY_UNKNOWN_PLATFORM)
		std::string os = "Unknown platform";
	#else
		#error "Big error"
	#endif

	#if   defined(TOY_32_BIT)
		std::string bit = "32bit";
	#elif defined(TOY_64_BIT)
		std::string bit = "64bit";
	#else
		#error "Big error"
	#endif

	#if   defined(TOY_NDK)
		std::string com = "Android NDK";
	#elif defined(TOY_MINGW)
		std::string com = "MinGW";
	#elif defined(TOY_LLVM)
		std::string com = "LLVM";
	#elif defined(TOY_GCC)
		std::string com = "GCC";
	#elif defined(TOY_VC_2017)
		std::string com = "Visual C++ 2017";
	#elif defined(TOY_VC_2015)
		std::string com = "Visual C++ 2015";
	#elif defined(TOY_MSVC)
		std::string com = "Visual C++(Undetection)";
	#elif defined(TOY_UNKNOWN_COMPILER)
		std::string com = "Unknown compiler";
	#else
		#error "Big error"
	#endif

	return os + " " + bit + " " + com;
}

inline void PrintInformation_English()
{
	toy::Log(TOY_TEXT("Information:\n"));
	toy::Log(TOY_TEXT("    Author    ToyAuthor\n"));
	toy::Log(TOY_TEXT("    License   Public Domain\n"));
	toy::Log(TOY_TEXT("    Website   https://toyauthor.github.io/ToyBoxDoc\n"));

	Logger<<TOY_TEXT("    Version   ")<<PrintVersion_GetVersion()<<toy::NextLine;
	Logger<<TOY_TEXT("    Platform  ")<<PrintInformation_GetPlatform()<<toy::NextLine;
}

inline void PrintInformation_TraditionalChinese()
{
	toy::Log(TOY_TEXT("程式資訊:\n"));
	toy::Log(TOY_TEXT("    作者      ToyAuthor\n"));
	toy::Log(TOY_TEXT("    授權條款  Public Domain\n"));
	toy::Log(TOY_TEXT("    網站      https://toyauthor.github.io/ToyBoxDoc\n"));

	Logger<<TOY_TEXT("    版本號    ")<<PrintVersion_GetVersion()<<toy::NextLine;
	Logger<<TOY_TEXT("    運行平台  ")<<PrintInformation_GetPlatform()<<toy::NextLine;
}

inline void PrintInformation_SimplifiedChinese()
{
	toy::Log(TOY_TEXT("软件资讯:\n"));
	toy::Log(TOY_TEXT("    作者      ToyAuthor\n"));
	toy::Log(TOY_TEXT("    许可协议  Public Domain\n"));
	toy::Log(TOY_TEXT("    网站      https://toyauthor.github.io/ToyBoxDoc\n"));

	Logger<<TOY_TEXT("    版本号    ")<<PrintVersion_GetVersion()<<toy::NextLine;
	Logger<<TOY_TEXT("    运行平台  ")<<PrintInformation_GetPlatform()<<toy::NextLine;
}

inline void PrintInformation(const SystemArgs &arg)
{
	if(arg.num>2)
	{
		std::string     param=arg[2];

		if(param=="-tc")   { PrintInformation_TraditionalChinese();  return; }
		if(param=="-sc")   { PrintInformation_SimplifiedChinese();   return; }
	}

	PrintInformation_English();
}
