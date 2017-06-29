
#include "toy/utf/Convert.hpp"
#include "toy/utf/ConvertUTF.hpp"


namespace toy{
namespace utf{


template<typename T>
inline void StripTrailing(T *str)
{
	//str->erase( std::find(str->begin(), str->end(), '\0') ,str->end());

	int  i = 0;
	int  size = str->size();

	for ( ; i<size ; i++ )
	{
		if ( (*str)[i]=='\0' ) break;
	}

	str->resize(i);
}

std::basic_string<wchar_t> UTF8ToWChar(const std::string str)
{
	std::basic_string<wchar_t>   result(str.size(),'\0');

	ConversionFlags  flag  = strictConversion;
	const uint8_t*   data8 = reinterpret_cast<const uint8_t*>(str.data());

	#if defined(TOY_WINDOWS)
		uint16_t*        data16 = const_cast<uint16_t*>(reinterpret_cast<const uint16_t*>(result.data()));
		ConversionResult error  = ConvertUTF8toUTF16( &data8, data8+str.size(), &data16, data16+result.size(), flag );
	#else
		uint32_t*        data32 = const_cast<uint32_t*>(reinterpret_cast<const uint32_t*>(result.data()));
		ConversionResult error  = ConvertUTF8toUTF32( &data8, data8+str.size(), &data32, data32+result.size(), flag );
	#endif

	(void)error;

	StripTrailing(&result);

	return result;
}

std::string WCharToUTF8(const std::basic_string<wchar_t> str)
{
	std::string    result(str.size()*4,'\0');

	ConversionFlags  flag  = strictConversion;
	uint8_t*         data8 = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(result.data()));

	#if defined(TOY_WINDOWS)
		const uint16_t*  data16 = reinterpret_cast<const uint16_t*>(str.data());
		ConversionResult error  = ConvertUTF16toUTF8( &data16, data16+str.size(), &data8, data8+result.size(), flag );
	#else
		const uint32_t*  data32 = reinterpret_cast<const uint32_t*>(str.data());
		ConversionResult error  = ConvertUTF32toUTF8( &data32, data32+str.size(), &data8, data8+result.size(), flag );
	#endif

	(void)error;

	StripTrailing(&result);

	return result;
}

std::basic_string<uint16_t> UTF8ToUTF16(const std::string str)
{
	std::basic_string<uint16_t>   result(str.size(),'\0');

	ConversionFlags    flag   = strictConversion;
	const uint8_t*     data8  = reinterpret_cast<const uint8_t*>(str.data());
	uint16_t*          data16 = const_cast<uint16_t*>(result.data());
	ConversionResult   error  = ConvertUTF8toUTF16( &data8, data8+str.size(), &data16, data16+result.size(), flag );

	(void)error;

	StripTrailing(&result);

	return result;
}

std::string UTF16ToUTF8(const std::basic_string<uint16_t> str)
{
	std::string    result(str.size()*4,'\0');

	ConversionFlags    flag   = strictConversion;
	const uint16_t*    data16 = str.data();
	uint8_t*           data8  = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(result.data()));
	ConversionResult   error  = ConvertUTF16toUTF8( &data16, data16+str.size(), &data8, data8+result.size(), flag );

	(void)error;

	StripTrailing(&result);

	return result;
}

std::basic_string<uint32_t> UTF8ToUTF32(const std::string str)
{
	std::basic_string<uint32_t>   result(str.size(),'\0');

	ConversionFlags    flag   = strictConversion;
	const uint8_t*     data8  = reinterpret_cast<const uint8_t*>(str.data());
	uint32_t*          data32 = const_cast<uint32_t*>(result.data());
	ConversionResult   error  = ConvertUTF8toUTF32( &data8, data8+str.size(), &data32, data32+result.size(), flag );

	(void)error;

	StripTrailing(&result);

	return result;
}

std::string UTF32ToUTF8(const std::basic_string<uint32_t> str)
{
	std::string    result(str.size()*4,'\0');

	ConversionFlags    flag   = strictConversion;
	const uint32_t*    data32 = str.data();
	uint8_t*           data8  = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(result.data()));
	ConversionResult   error  = ConvertUTF32toUTF8( &data32, data32+str.size(), &data8, data8+result.size(), flag );

	(void)error;

	StripTrailing(&result);

	return result;
}

std::basic_string<uint32_t> UTF16ToUTF32(const std::basic_string<uint16_t> str)
{
	std::basic_string<uint32_t>    result(str.size(),'\0');

	ConversionFlags    flag   = strictConversion;
	const uint16_t*    data16 = str.data();
	uint32_t*          data32 = const_cast<uint32_t*>(result.data());
	ConversionResult   error  = ConvertUTF16toUTF32( &data16, data16+str.size(), &data32, data32+result.size(), flag );

	(void)error;

	StripTrailing(&result);

	return result;
}

std::basic_string<uint16_t> UTF32ToUTF16(const std::basic_string<uint32_t> str)
{
	std::basic_string<uint16_t>    result(str.size()*2,'\0');

	ConversionFlags    flag   = strictConversion;
	const uint32_t*    data32 = str.data();
	uint16_t*          data16 = const_cast<uint16_t*>(result.data());
	ConversionResult   error  = ConvertUTF32toUTF16( &data32, data32+str.size(), &data16, data16+result.size(), flag );

	(void)error;

	StripTrailing(&result);

	return result;
}

void UTF8ToWChar( const char *input, wchar_t *output, int length )
{
	ConversionFlags  flag  = strictConversion;
	const uint8_t*   data8 = reinterpret_cast<const uint8_t*>(input);

	#if defined(TOY_WINDOWS)
		uint16_t*   data16 = reinterpret_cast<uint16_t*>(output);
		ConversionResult   error = ConvertUTF8toUTF16( &data8, data8+length, &data16, data16+length, flag );
	#else
		uint32_t*   data32 = reinterpret_cast<uint32_t*>(output);
		ConversionResult   error = ConvertUTF8toUTF32( &data8, data8+length, &data32, data32+length, flag );
	#endif
	(void)error;
}

void WCharToUTF8( const wchar_t *input, char *output, int length )
{
	ConversionFlags  flag  = strictConversion;
	uint8_t*         data8 = reinterpret_cast<uint8_t*>(output);

	#if defined(TOY_WINDOWS)
		const uint16_t*   data16 = reinterpret_cast<const uint16_t*>(input);
		ConversionResult   error = ConvertUTF16toUTF8( &data16, data16+length, &data8, data8+length*4, flag );
	#else
		const uint32_t*   data32 = reinterpret_cast<const uint32_t*>(input);
		ConversionResult   error = ConvertUTF32toUTF8( &data32, data32+length, &data8, data8+length*4, flag );
	#endif
	(void)error;
}

}}
