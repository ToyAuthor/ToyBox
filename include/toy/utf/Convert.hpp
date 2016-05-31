
#pragma once

#include "toy/Standard.hpp"


namespace toy{
namespace utf{

TOY_API std::basic_string<wchar_t> UTF8ToWChar(std::string str);
TOY_API std::string WCharToUTF8(std::basic_string<wchar_t> str);
TOY_API std::basic_string<uint16_t> UTF8ToUTF16(std::string str);
TOY_API std::basic_string<uint32_t> UTF8ToUTF32(std::string str);
TOY_API std::string UTF32ToUTF8(std::basic_string<uint32_t> str);

}}
