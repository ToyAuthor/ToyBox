
#pragma once

#include <cstdint>
#include <string>
#include "toy/CompilerConfig.hpp"

namespace toy{
namespace utf{

TOY_API auto WCharToUTF8(std::basic_string<wchar_t> str) ->std::string;

TOY_API auto UTF8ToWChar(std::string str) ->std::basic_string<wchar_t>;
TOY_API auto UTF8ToUTF16(std::string str) ->std::basic_string<uint16_t>;
TOY_API auto UTF8ToUTF32(std::string str) ->std::basic_string<uint32_t>;

TOY_API auto UTF16ToUTF32(std::basic_string<uint16_t> str) ->std::basic_string<uint32_t>;
TOY_API auto UTF16ToUTF8( std::basic_string<uint16_t> str) ->std::string;

TOY_API auto UTF32ToUTF16(std::basic_string<uint32_t> str) ->std::basic_string<uint16_t>;
TOY_API auto UTF32ToUTF8( std::basic_string<uint32_t> str) ->std::string;

TOY_API void UTF8ToWChar(const char    *input, wchar_t *output, int length);
TOY_API void WCharToUTF8(const wchar_t *input, char    *output, int length);

}}
