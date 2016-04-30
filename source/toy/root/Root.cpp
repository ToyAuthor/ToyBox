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
	return std::string("0.1");
}

std::string Root::GetPlatform()
{
	return "empty";
}

std::string Root::GetComment()
{
	return "empty";
}
