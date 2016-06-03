#include "toy/log/Printer.hpp"
#include "toy/Log.hpp"

namespace toy{

const log::Printer& NextLine(const log::Printer& m)
{
	toy::Log("\n");
	return m;
}

}

using namespace toy;
using namespace log;

const Printer& Printer:: operator << (const int num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const float num) const
{
	toy::Log("%f",num);
	return *this;
}

const Printer& Printer:: operator << (std::string str) const
{
	toy::Log("%s",str.c_str());
	return *this;
}

const Printer& Printer:: operator << (std::wstring str) const
{
	toy::Log(L"%ls",str.c_str());
	return *this;
}

const Printer& Printer:: operator << (const Printer& (*func)(const Printer&)) const
{
	return func(*this);
}
