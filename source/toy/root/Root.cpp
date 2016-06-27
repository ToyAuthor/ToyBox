#include "toy/root/Root.hpp"

using namespace toy;

Root::Root()
{
	;
}

Root::~Root()
{
	;
}

std::string Root::GetVersion()
{
	//return std::string("0.0.0");
	return std::string("debug mode");
}

std::string Root::GetOperatingSystem()
{
	#if   defined(TOY_ANDROID)
		return std::string("Android");
	#elif defined(TOY_LINUX)
		return std::string("Linux");
	#elif defined(TOY_MAC)
		return std::string("Mac OS");
	#elif defined(TOY_WINDOWS)
		return std::string("Windows");
	#elif defined(TOY_UNKNOWN_PLATFORM)
		return std::string("Unknown platform");
	#else
		#error "Big error"
	#endif
}

std::string Root::GetSystemType()
{
	#if   defined(TOY_32_BIT)
		return std::string("32bit");
	#elif defined(TOY_64_BIT)
		return std::string("64bit");
	#else
		#error "Big error"
	#endif
}

std::string Root::GetComplierName()
{
	#if   defined(TOY_NDK)
		return std::string("Android NDK");
	#elif defined(TOY_MINGW)
		return std::string("MinGW");
	#elif defined(TOY_LLVM)
		return std::string("LLVM");
	#elif defined(TOY_GCC)
		return std::string("GCC");
	#elif defined(TOY_VC_2015)
		return std::string("Visual C++ 2015");
	#elif defined(TOY_MSVC)
		return std::string("Visual C++(Undetection)");
	#elif defined(TOY_UNKNOWN_COMPILER)
		return std::string("Unknown compiler");
	#else
		#error "Big error"
	#endif
}

std::string Root::GetPlatform()
{
	std::string   os  = GetOperatingSystem();
	std::string   bit = GetSystemType();
	std::string   com = GetComplierName();

	return os + " " + bit + " " + com;
}

std::string Root::GetComment()
{
	std::string comment("It's not ready yet!\n");
	return comment + __DATE__ + " " + __TIME__;
}
