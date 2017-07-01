
#pragma once

#include <toy/Root.hpp>
#include "SystemArgs.hpp"

using toy::Logger;

inline void PrintOptionList_English()
{
	toy::Log("    player.exe               # Read default-config.lua in current directory\n");
	toy::Log("    player.exe --copyright   # Show copyright of ToyBox\n");
	toy::Log("    player.exe --example     # Example for reading config file\n");
	toy::Log("    player.exe --help        # English\n");
	toy::Log("    player.exe --help -sc    # 简体中文\n");
	toy::Log("    player.exe --help -tc    # 繁體中文\n");
	toy::Log("    player.exe --info        # Get more information\n");
	toy::Log("    player.exe --version     # Show version of ToyBox\n");
	toy::Log("    player.exe --reset       # Reset default-config.lua\n");
}

inline void PrintOptionList_TraditionalChinese()
{
	toy::Log("    player.exe                   # 讀取當前資料夾的default-config.lua\n");
	toy::Log("    player.exe --copyright -tc   # 顯示版權聲明\n");
	toy::Log("    player.exe --example -tc     # 顯示讀取設定檔的使用範例\n");
	toy::Log("    player.exe --help -tc        # 顯示使用說明\n");
	toy::Log("    player.exe --info -tc        # 顯示程式內部資訊\n");
	toy::Log("    player.exe --version -tc     # 顯示版本資訊\n");
	toy::Log("    player.exe --reset -tc       # 將預設讀取的設定檔恢復回預設內容\n");
}

inline void PrintOptionList_SimplifiedChinese()
{
	toy::Log("    player.exe                   # 读取当前资料夹的default-config.lua\n");
	toy::Log("    player.exe --copyright -sc   # 显示版权声明\n");
	toy::Log("    player.exe --example -sc     # 显示读取设定档的使用范例\n");
	toy::Log("    player.exe --help -sc        # 显示使用说明\n");
	toy::Log("    player.exe --info -tc        # 显示软件内部资讯\n");
	toy::Log("    player.exe --version -sc     # 显示版本资讯\n");
	toy::Log("    player.exe --reset -sc       # 将预设读取的设定档恢复回预设内容\n");
}

inline void PrintHelp_English()
{
	toy::Log("Usage:\n");
	PrintOptionList_English();
}

inline void PrintHelp_TraditionalChinese()
{
	toy::Log("使用說明:\n");
	PrintOptionList_TraditionalChinese();
}

inline void PrintHelp_SimplifiedChinese()
{
	toy::Log("使用说明:\n");
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

inline void PrintVersion_English()
{
	/*
	 * The symbol "%s" only work for ansi key code.
	 * And the symbol "%ls" only work for wide character.
	 * So toy::Logger is the only one choice.
	 */
	Logger<<"ToyBox version "<<toy::Root::GetVersion()<<toy::NextLine;
}

inline void PrintVersion_TraditionalChinese()
{
	Logger<<"ToyBox 當前版本為 "<<toy::Root::GetVersion()<<toy::NextLine;
}

inline void PrintVersion_SimplifiedChinese()
{
	Logger<<"ToyBox 当前版本为 "<<toy::Root::GetVersion()<<toy::NextLine;
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
			Logger<<"沒有"<<cmd<<"這個指令，只有提供下列選項:"<<toy::NextLine<<toy::NextLine;
			PrintOptionList_TraditionalChinese();
			return;
		}
		if(param=="-sc")
		{
			Logger<<"没有"<<cmd<<"这个指令，只有提供下列选项:"<<toy::NextLine<<toy::NextLine;
			PrintOptionList_SimplifiedChinese();
			return;
		}
	}

	Logger<<"Command "<<cmd<<" doesn't exist! You just only have following options:"<<toy::NextLine<<toy::NextLine;
	PrintOptionList_English();
}

inline void PrintExample_English()
{
	toy::Log("For examples:\n");
	toy::Log("    player.exe d:configs/default-config.lua    # General usage\n");
	toy::Log("    player.exe                                 # Read \"default-config.lua\" in the working directory\n");
}

inline void PrintExample_TraditionalChinese()
{
	toy::Log("使用範例:\n");
	toy::Log("    player.exe d:configs/default-config.lua    # 一般用法\n");
	toy::Log("    player.exe                                 # 讀當前資料夾的\"default-config.lua\"設定檔\n");
}

inline void PrintExample_SimplifiedChinese()
{
	toy::Log("使用范例:\n");
	toy::Log("    player.exe d:configs/default-config.lua    # 一般用法\n");
	toy::Log("    player.exe                                 # 读当前资料夹的\"default-config.lua\"设定档\n");
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
	toy::Log("    Copyright (c) 2014-2016 ToyAuthor\n");
	toy::Log("\n");

	toy::Log("    This software is a part of ToyBox.\n");
	toy::Log("    ToyBox is release into public domain.\n");
	toy::Log("    Be careful, those third party libraries have their own license.\n");
	toy::Log("    The font files have their own license too.\n");
	toy::Log("    The others resources are belong to public domain.(scripts,images...etc)\n");
	toy::Log("    I recommand you keep the license folder.\n");
}

inline void PrintCopyright_TraditionalChinese()
{
	toy::Log("    Copyright (c) 2014-2016 ToyAuthor\n");
	toy::Log("\n");

	toy::Log("    本程式屬於 ToyBox 的一部份\n");
	toy::Log("    ToyBox 本身是以 Public Domain 形式發佈的軟體\n");
	toy::Log("    但是要注意內部所引用的第三方工具有著各自的授權條款\n");
	toy::Log("    至於腳本文字檔與圖片皆沒有保留著作權或者附帶授權條款\n");
	toy::Log("    可以自由使用\n");
	toy::Log("    建議別刪掉用來做版權聲明的 license 資料夾\n");
}

inline void PrintCopyright_SimplifiedChinese()
{
	toy::Log("    Copyright (c) 2014-2016 ToyAuthor\n");
	toy::Log("\n");

	toy::Log("    本软件属于 ToyBox 的一部份\n");
	toy::Log("    ToyBox 本身是以 Public Domain 形式发布的软件\n");
	toy::Log("    但是要注意内部所引用的第三方工具有着各自的许可协议\n");
	toy::Log("    至于脚本文字档与图片皆没有附带着作权以及许可协议\n");
	toy::Log("    可以自由使用\n");
	toy::Log("    建议别删掉用来做版权声明的 license 资料夹\n");
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

inline void PrintInformation_English()
{
	toy::Log("Information:\n");
	toy::Log("    Author    ToyAuthor\n");
	toy::Log("    License   Public Domain\n");
	toy::Log("    Website   https://github.com/ToyAuthor/ToyBoxPlayer\n");

	Logger<<"    Version   "<<toy::Root::GetVersion()<<toy::NextLine;
	Logger<<"    Platform  "<<toy::Root::GetPlatform()<<toy::NextLine;
}

inline void PrintInformation_TraditionalChinese()
{
	toy::Log("程式資訊:\n");
	toy::Log("    作者      ToyAuthor\n");
	toy::Log("    授權條款  Public Domain\n");
	toy::Log("    網站      https://github.com/ToyAuthor/ToyBoxPlayer\n");

	Logger<<"    版本號    "<<toy::Root::GetVersion()<<toy::NextLine;
	Logger<<"    運行平台  "<<toy::Root::GetPlatform()<<toy::NextLine;
}

inline void PrintInformation_SimplifiedChinese()
{
	toy::Log("软件资讯:\n");
	toy::Log("    作者      ToyAuthor\n");
	toy::Log("    许可协议  Public Domain\n");
	toy::Log("    网站      https://github.com/ToyAuthor/ToyBoxPlayer\n");

	Logger<<"    版本号    "<<toy::Root::GetVersion()<<toy::NextLine;
	Logger<<"    运行平台  "<<toy::Root::GetPlatform()<<toy::NextLine;
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
