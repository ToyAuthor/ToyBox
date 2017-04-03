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
	//return "0.0.1";
	return "0.0.0.x debug mode";
}

std::string Root::GetOperatingSystem()
{
	#if   defined(TOY_ANDROID)
		return "Android";
	#elif defined(TOY_LINUX)
		return "Linux";
	#elif defined(TOY_MAC)
		return "Mac OS";
	#elif defined(TOY_WINDOWS)
		return "Windows";
	#elif defined(TOY_UNKNOWN_PLATFORM)
		return "Unknown platform";
	#else
		#error "Big error"
	#endif
}

std::string Root::GetSystemType()
{
	#if   defined(TOY_32_BIT)
		return "32bit";
	#elif defined(TOY_64_BIT)
		return "64bit";
	#else
		#error "Big error"
	#endif
}

std::string Root::GetComplierName()
{
	#if   defined(TOY_NDK)
		return "Android NDK";
	#elif defined(TOY_MINGW)
		return "MinGW";
	#elif defined(TOY_LLVM)
		return "LLVM";
	#elif defined(TOY_GCC)
		return "GCC";
	#elif defined(TOY_VC_2017)
		return "Visual C++ 2017";
	#elif defined(TOY_VC_2015)
		return "Visual C++ 2015";
	#elif defined(TOY_MSVC)
		return "Visual C++(Undetection)";
	#elif defined(TOY_UNKNOWN_COMPILER)
		return "Unknown compiler";
	#else
		#error "Big error"
	#endif
}

std::string Root::GetPlatform()
{
	auto   os  = GetOperatingSystem();
	auto   bit = GetSystemType();
	auto   com = GetComplierName();

	return os + " " + bit + " " + com;
}

std::string Root::GetComment()
{
	std::string comment("It's not ready yet!\n");
	return comment + __DATE__ + " " + __TIME__;
}
