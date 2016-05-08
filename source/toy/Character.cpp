#include <cstdio>
#include "toy/Windows.hpp"
#include "toy/Character.hpp"


#if defined(TOY_LINUX) || defined(TOY_MAC)
#include <iconv.h>
#include <cstring>
#include <cerrno>
#endif

namespace toy{

#if defined(TOY_WINDOWS)

void Utf8ToWChar(wchar_t *output,const char *input,int length)
{
	MultiByteToWideChar( CP_UTF8, 0, input, -1, output, length+1 );
}

void WCharToUtf8(char *output,const wchar_t *input,int length)
{
	WideCharToMultiByte( CP_UTF8, 0, input, -1, output, length+1, NULL, NULL );
}

#endif//TOY_WINDOWS

#if defined(TOY_LINUX) || defined(TOY_MAC)

void Utf8ToWChar(wchar_t *output,const char *input,int length)
{
	size_t     result;
	iconv_t    env;

	int size = length+1;
	env = iconv_open("WCHAR_T","UTF-8");

	if (env==(iconv_t)-1)
	{
		printf("iconv_open UTF8->WCHAR_T error %d/n",errno);
	}

	result = iconv(env,(char**)&input,(size_t*)&size,(char**)&output,(size_t*)&length);

	if (result==(size_t)-1)
	{
		printf("iconv UTF8->WCHAR_T error %d/n",errno);
	}

	iconv_close(env);
}

void WCharToUtf8(char *output,const wchar_t *input,int length)
{
	size_t    result;
	iconv_t   env;

	env = iconv_open("UTF-8","WCHAR_T");

	if (env==(iconv_t)-1)
	{
		printf("iconv_open WCHAR_T->UTF8 error%s %d/n",strerror(errno),errno);
	}

	result = iconv(env,(char**)&input,(size_t*)&length,(char**)&output,(size_t*)&length);

	if (result==(size_t)-1)
	{
		printf("iconv WCHAR_T->UTF8 error %d/n",errno);
	}

	iconv_close(env);
}

#endif//TOY_LINUX


}//namespace toy{
