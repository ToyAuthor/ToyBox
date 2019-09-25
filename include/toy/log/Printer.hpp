
#pragma once

#include <cstdint>
#include <string>
#include "toy/CompilerConfig.hpp"

namespace toy{
namespace log{

class TOY_API Printer
{
	public:

		Printer(){}
		~Printer(){}

		const Printer& operator << (const int8_t) const;
		const Printer& operator << (const uint8_t) const;
		const Printer& operator << (const int16_t) const;
		const Printer& operator << (const uint16_t) const;
		const Printer& operator << (const int32_t) const;
		const Printer& operator << (const uint32_t) const;
		const Printer& operator << (const int64_t) const;
		const Printer& operator << (const uint64_t) const;

		const Printer& operator << (const float) const;
		const Printer& operator << (const double) const;
		const Printer& operator << (const unsigned char *str) const;
		const Printer& operator << (      char *const str) const;
		const Printer& operator << (const char *const str) const;
		const Printer& operator << (const std::string &str) const;
		const Printer& operator << (      wchar_t *const str) const;
		const Printer& operator << (const wchar_t *const str) const;
		const Printer& operator << (const std::wstring &str) const;
		const Printer& operator << (const std::string *str) const;
		const Printer& operator << (const std::wstring *str) const;
		const Printer& operator << (const Printer& (*func)(const Printer&)) const;
		const Printer& operator << (const std::exception &e) const;

		template<typename T>
		const Printer& operator << (const T &obj) const
		{
			(*this)<<obj.str();
			return *this;
		}

	#if !defined(TOY_WINDOWS) && !defined(TOY_LINUX) && !defined(TOY_MAC)
		const Printer& operator << (const int) const;
	#endif
	#if !defined(TOY_LINUX)
		const Printer& operator << (const long int) const;
	#endif
	#if !defined(TOY_WINDOWS) && !defined(TOY_MAC)
		const Printer& operator << (const long long) const;
	#endif
	#if !defined(TOY_WINDOWS) && !defined(TOY_LINUX) && !defined(TOY_MAC)
		const Printer& operator << (const unsigned int) const;
	#endif
	#if !defined(TOY_LINUX)
		const Printer& operator << (const unsigned long int) const;
	#endif
	#if !defined(TOY_WINDOWS) && !defined(TOY_MAC)
		const Printer& operator << (const unsigned long long) const;
	#endif
};

}}

namespace toy{
TOY_API extern const log::Printer& NewLine(const log::Printer& m);
TOY_API extern log::Printer Logger;
}
