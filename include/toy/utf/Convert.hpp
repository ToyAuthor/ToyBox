
#pragma once

#include <cstdint>
#include <string>
#include "toy/CompilerConfig.hpp"

namespace toy{
namespace utf{

TOY_API std::basic_string<wchar_t> UTF8ToWChar(std::string str);
TOY_API std::string WCharToUTF8(std::basic_string<wchar_t> str);

TOY_API std::basic_string<uint16_t> UTF8ToUTF16(std::string str);
TOY_API std::basic_string<uint32_t> UTF8ToUTF32(std::string str);
TOY_API std::basic_string<uint32_t> UTF16ToUTF32(std::basic_string<uint16_t> str);
TOY_API std::basic_string<uint16_t> UTF32ToUTF16(std::basic_string<uint32_t> str);
TOY_API std::string UTF16ToUTF8(std::basic_string<uint16_t> str);
TOY_API std::string UTF32ToUTF8(std::basic_string<uint32_t> str);

TOY_API void UTF8ToWChar(const char    *input, wchar_t  *output, int length);
TOY_API void WCharToUTF8(const wchar_t *input, char     *output, int length);

}}
