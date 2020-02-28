
#include <cstdio>
#include <memory>
#include "toy/CompilerConfig.hpp"
#include "toy/Exception.hpp"

namespace toy{

TOY_API extern void Execute(const char* cmd);

void Execute(const char* cmd)
{
	#ifdef TOY_WINDOWS
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "w"), _pclose);
	#else
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "w"), pclose);
	#endif

	if ( !pipe ) throw toy::Exception(TOY_MARK);
}

}

/*
std::string execute(const char* cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

	if (!pipe)
	{
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}

	return result;
}*/
