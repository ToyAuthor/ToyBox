
#pragma once

#include "toy/CompilerConfig.hpp"


namespace toy{

TOY_API void Utf8ToWChar(wchar_t  *output,const char    *input,int length);
TOY_API void WCharToUtf8(char     *output,const wchar_t *input,int length);

}
