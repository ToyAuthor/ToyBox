/**
 * @file   Log.hpp
 * @brief  A wrapper for printing message.
 */

#pragma once

#include <cstdio>
#include <string>
#include <toy/log/Printer.hpp>

namespace lua{
namespace log{


class Printer
{
	private:

		toy::log::Printer _log;

	public:

		Printer(){}
		~Printer(){}

		void _newline() const
		{
			_log<<toy::NewLine;
		}

		const Printer& operator << (const int num) const
		{
			//std::printf("%d",num);
			_log<<(int32_t)num;
			return *this;
		}

		const Printer& operator << (const long int num) const
		{
			//std::printf("%ld",num);
			_log<<(int32_t)num;
			return *this;
		}

		const Printer& operator << (const long long num) const
		{
			/*#ifdef _WIN64
			std::printf("%lld",num);
			#elif defined(_WIN32)
			std::printf("%I64d",num);
			#else
			std::printf("%lld",num);
			#endif*/
			_log<<(int64_t)num;
			return *this;
		}

		const Printer& operator << (const float num) const
		{
			//std::printf("%f",num);
			_log<<num;
			return *this;
		}

		const Printer& operator << (const double num) const
		{
			//std::printf("%f",num);
			_log<<num;
			return *this;
		}

		const Printer& operator << (std::string str) const
		{
			//std::printf("%s",str.c_str());
			_log<<str;
			return *this;
		}

		const Printer& operator << (std::wstring str) const
		{
			//std::wprintf(L"%ls",str.c_str());
			_log<<str;
			return *this;
		}

		const Printer& operator << (std::string *str) const
		{
			//std::printf("%s",str->c_str());
			_log<<*str;
			return *this;
		}

		const Printer& operator << (std::wstring *str) const
		{
			//std::wprintf(L"%ls",str->c_str());
			_log<<*str;
			return *this;
		}

		const Printer& operator << (const Printer& (*func)(const Printer&)) const
		{
			return func(*this);
		}
};

}//namespace log

inline const ::lua::log::Printer& End(const ::lua::log::Printer& m)
{
	//std::printf(" - luapp message\n");
	m<<" - luapp message";
	m._newline();
	return m;
}

static ::lua::log::Printer      Log;

}//namespace lua
