#include <cstdarg>
#include <string>
#include <cstring>
#include "toy/Log.hpp"
#include "toy/Windows.hpp"
#include "toy/Character.hpp"
#include "toy/Utf.hpp"

#define STRING_SIZE 128


void toy::Log(const char *fmt, ... )
{
	va_list         argptr;
	va_start(argptr, fmt);

	#if defined(TOY_WINDOWS)
		DWORD     ws;
		char      bufferA[STRING_SIZE];
		wchar_t   bufferW[STRING_SIZE];

		vsnprintf(bufferA,STRING_SIZE,fmt,argptr);
		toy::Utf8ToWChar(bufferW,bufferA,std::strlen(bufferA));
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),bufferW,std::wcslen(bufferW),&ws,nullptr);
	#else
		char      buffer[STRING_SIZE];
		std::vsnprintf(buffer,STRING_SIZE,fmt,argptr);
		std::printf("%s",buffer);
	#endif

	va_end(argptr);
}

void toy::Log(const wchar_t *fmt, ... )
{
	va_list         argptr;
	va_start(argptr, fmt);

	wchar_t      buffer[STRING_SIZE];

	#if defined(TOY_WINDOWS)
		#if defined(TOY_MSVC)
			_vsnwprintf_s(buffer,STRING_SIZE,(int)STRING_SIZE-1,fmt,argptr);
		#elif defined(TOY_MINGW)
			vsnwprintf(buffer,STRING_SIZE,fmt,argptr);
		#else
			vswprintf(buffer,STRING_SIZE,fmt,argptr);   // Just in case.
		#endif

		DWORD			ws;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),buffer,std::wcslen(buffer),&ws,nullptr);
	#else
		//wprintf(fmt,argptr);    // No. It doesn't work on Linux.
		std::vswprintf(buffer,STRING_SIZE,fmt,argptr);
		std::printf("%s",toy::utf::WCharToUTF8(std::wstring(buffer)).c_str());
	#endif

	va_end(argptr);
}

void toy::Log(const std::exception &except)
{
	toy::Log("%s\n",except.what());
}

#undef STRING_SIZE
