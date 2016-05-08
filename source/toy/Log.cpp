#include <cstdarg>
#include <string>
#include <cstring>
#include "toy/Log.hpp"
#include "toy/Windows.hpp"
#include "toy/Character.hpp"


#define STRING_SIZE 128


void toy::Log(const char *fmt, ... )
{
	va_list         argptr;

	va_start(argptr, fmt);

	char      buffer[STRING_SIZE];

	vsnprintf(buffer,STRING_SIZE,fmt,argptr);

	#if defined(TOY_WINDOWS)
		DWORD			ws;
		wchar_t         buffer2[STRING_SIZE];

		toy::Utf8ToWChar(buffer2,buffer,std::strlen(buffer));
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),buffer2,wcslen(buffer2),&ws,NULL);
	#else
		printf("%s",buffer);
	#endif

	va_end(argptr);
}

void toy::Log(const wchar_t *fmt, ... )
{
	va_list         argptr;

	va_start(argptr, fmt);

	wchar_t      buffer[STRING_SIZE];

	#if defined(TOY_MSVC)
		_vsnwprintf_s(buffer,STRING_SIZE,(int)STRING_SIZE-1,fmt,argptr);
	#elif defined(TOY_MINGW)
		vsnwprintf(buffer,STRING_SIZE,fmt,argptr);
	#else
		vsnprintf(buffer,STRING_SIZE,fmt,argptr);   // It's wrong.
	#endif

	#if defined(TOY_WINDOWS)
		DWORD			ws;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),buffer,wcslen(buffer),&ws,NULL);
	#else
		printf("%s",buffer);  // It's wrong.
	#endif

	va_end(argptr);
}

void toy::Log(toy::Exception except)
{
	toy::Log("%s:%d\n",std::string(except.message).c_str(),except.line);
}

#undef STRING_SIZE
