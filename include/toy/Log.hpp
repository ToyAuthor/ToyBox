
#pragma once

#include <functional>
#include "toy/log/Printer.hpp"

#define TOY_OPTION_ENABLE_PLUGIN_LOG_SYSTEM 1

namespace toy{

TOY_API extern void Log(const char *fmt, ... );
TOY_API extern void Log(const wchar_t *fmt, ... );
TOY_API extern void Log(const std::exception &);

#if TOY_OPTION_ENABLE_PLUGIN_LOG_SYSTEM

namespace log{
TOY_API extern void PushDevice(std::function<void(const char*)>,std::function<void(const wchar_t*)>);
TOY_API extern void PopDevice();
TOY_API extern void BackDefaultDevice();
}

#endif

}

//-----------------Uage-----------------start
#if 0
toy::io::Writer<>   writer("note.txt");

toy::log::PushDevice( [&writer](const char* str){writer.printf(str);},
                      [&writer](const wchar_t* str){writer.printf(toy::utf::WCharToUTF8(str).c_str());});

toy::Logger<<"Say something"<<toy::NewLine;

toy::log::PopDevice();
#endif
//-----------------Uage-----------------end
