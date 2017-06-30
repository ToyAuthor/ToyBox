
#pragma once

#include <cstdint>
#include <string>
#include "toy/CompilerConfig.hpp"

#if TOY_OPTION_CHECK_CAREFUL
#include "toy/Mark.hpp"
#include "toy/Log.hpp"
#endif

namespace toy{
namespace utf{

TOY_API auto WCharToUTF8(const std::basic_string<wchar_t> str) ->std::string;

TOY_API auto UTF8ToWChar(const std::string str) ->std::basic_string<wchar_t>;
TOY_API auto UTF8ToUTF16(const std::string str) ->std::basic_string<uint16_t>;
TOY_API auto UTF8ToUTF32(const std::string str) ->std::basic_string<uint32_t>;

TOY_API auto UTF16ToUTF32(const std::basic_string<uint16_t> str) ->std::basic_string<uint32_t>;
TOY_API auto UTF16ToUTF8( const std::basic_string<uint16_t> str) ->std::string;

TOY_API auto UTF32ToUTF16(const std::basic_string<uint32_t> str) ->std::basic_string<uint16_t>;
TOY_API auto UTF32ToUTF8( const std::basic_string<uint32_t> str) ->std::string;

TOY_API void UTF8ToWChar(const char    *input, wchar_t *output, int length);
TOY_API void WCharToUTF8(const wchar_t *input, char    *output, int length);

inline bool IsUtf8(const std::string &source)
{
	// Check the T of std::basic_string<T> is "signed char".
	#if TOY_OPTION_CHECK_CAREFUL
		signed char             tempChar2 = -1;
		std::string::value_type tempChar1 = tempChar2;
		if ( tempChar1>0 )
		{
			toy::Oops(TOY_MARK);
		}
	#endif

	for ( auto &c : source)
	{
		if ( c<0 )
		{
			return true;
		}
	}

	return false;
}

}}
