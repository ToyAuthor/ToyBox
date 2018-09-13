#include "toy/log/Printer.hpp"
#include "toy/Log.hpp"

namespace toy{

log::Printer Logger;

const log::Printer& NewLine(const log::Printer& m)
{
	toy::Log("\r\n");
	return m;
}

const log::Printer& NextLine(const log::Printer& m)
{
	toy::Log("\r\n");
	return m;
}

}

using namespace toy;
using namespace log;
/*
const Printer& Printer:: operator << (const int num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const long int num) const
{
	toy::Log("%ld",num);
	return *this;
}

const Printer& Printer:: operator << (const long long num) const
{
	#ifdef TOY_WIN64
	toy::Log("%lld",num);
	#elif defined(TOY_WIN32)
	toy::Log("%I64d",num);
	#else
	toy::Log("%lld",num);
	#endif
	return *this;
}

const Printer& Printer:: operator << (const unsigned int num) const
{
	toy::Log("%u",num);
	return *this;
}

const Printer& Printer:: operator << (const unsigned long int num) const
{
	toy::Log("%lu",num);
	return *this;
}

const Printer& Printer:: operator << (const unsigned long long num) const
{
	#ifdef TOY_WIN64
	toy::Log("%llu",num);
	#elif defined(TOY_WIN32)
	toy::Log("%I64u",num);
	#else
	toy::Log("%llu",num);
	#endif
	return *this;
}
*/
const Printer& Printer:: operator << (const int8_t num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const uint8_t num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const int16_t num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const uint16_t num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const int32_t num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const uint32_t num) const
{
	toy::Log("%d",num);
	return *this;
}

const Printer& Printer:: operator << (const int64_t num) const
{
	#ifdef TOY_WIN64
	toy::Log("%lld",num);
	#elif defined(TOY_WIN32)
	toy::Log("%I64d",num);
	#else
	toy::Log("%lld",num);
	#endif
	return *this;
}

const Printer& Printer:: operator << (const uint64_t num) const
{
	#ifdef TOY_WIN64
	toy::Log("%llu",num);
	#elif defined(TOY_WIN32)
	toy::Log("%I64u",num);
	#else
	toy::Log("%llu",num);
	#endif
	return *this;
}

const Printer& Printer:: operator << (const float num) const
{
	toy::Log("%f",num);
	return *this;
}

const Printer& Printer:: operator << (const double num) const
{
//	toy::Log("%lf",num);   // ISO C++ does not support this?
	toy::Log("%f",num);
	return *this;
}

const Printer& Printer:: operator << (const unsigned char *str) const
{
	toy::Log("%s",str);
	return *this;
}

const Printer& Printer:: operator << (char *const str) const
{
	toy::Log("%s",str);
	return *this;
}

const Printer& Printer:: operator << (const char *const str) const
{
	toy::Log("%s",str);
	return *this;
}

const Printer& Printer:: operator << (const std::string &str) const
{
	toy::Log("%s",str.c_str());
	return *this;
}

const Printer& Printer:: operator << (wchar_t *const str) const
{
	toy::Log(L"%ls",str);
	return *this;
}

const Printer& Printer:: operator << (const wchar_t *const str) const
{
	toy::Log(L"%ls",str);
	return *this;
}

const Printer& Printer:: operator << (const std::wstring &str) const
{
	toy::Log(L"%ls",str.c_str());
	return *this;
}

const Printer& Printer:: operator << (const std::string *str) const
{
	toy::Log("%s",str->c_str());
	return *this;
}

const Printer& Printer:: operator << (const std::wstring *str) const
{
	toy::Log(L"%ls",str->c_str());
	return *this;
}

const Printer& Printer:: operator << (const Printer& (*func)(const Printer&)) const
{
	return func(*this);
}

const Printer& Printer:: operator << (const std::exception &e) const
{
	(*this)<<"ToyBox Exception:"<<e.what();
	return *this;
}
