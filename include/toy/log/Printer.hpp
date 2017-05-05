
#pragma once

#include <string>
#include "toy/CompilerConfig.hpp"

namespace toy{
namespace log{

class TOY_API Printer
{
	public:

		Printer(){}
		~Printer(){}

		const Printer& operator << (const int) const;
		const Printer& operator << (const long int) const;
		const Printer& operator << (const long long) const;
		const Printer& operator << (const unsigned int) const;
		const Printer& operator << (const unsigned long int) const;
		const Printer& operator << (const unsigned long long) const;
		const Printer& operator << (const float) const;
		const Printer& operator << (const double) const;
		const Printer& operator << (const unsigned char *str) const;
		const Printer& operator << (const std::string str) const;
		const Printer& operator << (const std::wstring str) const;
		const Printer& operator << (const std::string *str) const;
		const Printer& operator << (const std::wstring *str) const;
		const Printer& operator << (const Printer& (*func)(const Printer&)) const;
};

}}

namespace toy{
TOY_API extern const log::Printer& NextLine(const log::Printer& m);
TOY_API extern log::Printer Logger;
}
