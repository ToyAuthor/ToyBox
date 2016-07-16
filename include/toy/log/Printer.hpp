
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
		const Printer& operator << (const float) const;
		const Printer& operator << (std::string str) const;
		const Printer& operator << (std::wstring str) const;
		const Printer& operator << (std::string *str) const;
		const Printer& operator << (std::wstring *str) const;
		const Printer& operator << (const Printer& (*func)(const Printer&)) const;
};

}}

namespace toy{
TOY_API const log::Printer& NextLine(const log::Printer& m);
extern TOY_API log::Printer Logger;
}
