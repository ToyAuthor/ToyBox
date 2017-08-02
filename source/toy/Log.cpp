#include <cstdarg>
#include <string>
#include <cstring>
#include <functional>
#include "toy/Log.hpp"
#include "toy/Windows.hpp"
#include "toy/Utf.hpp"

#ifdef TOY_ANDROID
#include <android/log.h>
#endif


//----------------PrintStr let you decide how to print string----------------start

namespace toy{
namespace log{

#if defined(TOY_WINDOWS)
	static std::function<void(const char*)> PrintStr = [](const char *str)
	{
		auto      word = utf::UTF8ToWChar(std::string(str));
		DWORD     ws;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),word.c_str(),word.size(),&ws,nullptr);
	};

	static std::function<void(const wchar_t*)> PrintStrW = [](const wchar_t *str)
	{
		DWORD     ws;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),str,std::wcslen(str),&ws,nullptr);
	};
#elif defined(TOY_ANDROID)
	// adb logcat toybox:D *:S
	static std::function<void(const char*)> PrintStr = [](const char *str)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "toybox", "%s", str);
	};

	// It still print nothing.
	static std::function<void(const wchar_t*)> PrintStrW = [](const wchar_t *str)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "toybox", "%s", utf::WCharToUTF8(std::wstring(str)).c_str());
	//	__android_log_print(ANDROID_LOG_DEBUG, "toybox", "%ls", str);
	};
#else
	static std::function<void(const char*)> PrintStr = [](const char *str)
	{
		std::printf("%s",str);
	};

	static std::function<void(const wchar_t*)> PrintStrW = [](const wchar_t *str)
	{
		//wprintf(L"%ls",str);    // No. It doesn't works on Linux.
		std::printf("%s",utf::WCharToUTF8(std::wstring(str)).c_str());
	};
#endif

}//namespace log
}//namespace toy

void toy::log::SetDevice(std::function<void(const char*)> func)
{
	toy::log::PrintStr = std::move(func);
}

void toy::log::SetDevice(std::function<void(const wchar_t*)> func)
{
	toy::log::PrintStrW = std::move(func);
}

//----------------PrintStr let you decide how to print string----------------end



#define STRING_SIZE 128

void toy::Log(const char *fmt, ... )
{
	va_list         argptr;
	va_start(argptr, fmt);

	char      buffer[STRING_SIZE];
	#if defined(TOY_ANDROID)
		vsnprintf(buffer,STRING_SIZE,fmt,argptr);
	#else
		std::vsnprintf(buffer,STRING_SIZE,fmt,argptr);
	#endif
	buffer[STRING_SIZE-1] = '\0';
	toy::log::PrintStr(buffer);

	va_end(argptr);
}

void toy::Log(const wchar_t *fmt, ... )
{
	va_list         argptr;
	va_start(argptr, fmt);

	wchar_t      buffer[STRING_SIZE];

	#if defined(TOY_MSVC)
		_vsnwprintf_s(buffer,STRING_SIZE,(int)STRING_SIZE-1,fmt,argptr);
	#elif defined(TOY_ANDROID)// || defined(TOY_MINGW)
		vswprintf(buffer,STRING_SIZE,fmt,argptr);
	#elif defined(TOY_MINGW)
		vsnwprintf(buffer,STRING_SIZE,fmt,argptr);
	#else
		std::vswprintf(buffer,STRING_SIZE,fmt,argptr);
	#endif

	buffer[STRING_SIZE-1] = L'\0';
	toy::log::PrintStrW(buffer);

	va_end(argptr);
}

void toy::Log(const std::exception &except)
{
	toy::Log("%s\n",except.what());
}

#undef STRING_SIZE
