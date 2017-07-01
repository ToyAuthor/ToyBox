
#pragma once


#include <toy/Standard.hpp>

struct SystemArgs
{
	SystemArgs(int _argc, char** _argv)
	{
		num =_argc;
		argv=_argv;

		// Just in case.
		if(num<1)
		{
			toy::Log("Error:Arguments count should bigger than zero.\n");
		}
	}

	std::string operator [](int index) const
	{
		return std::string(argv[index]);
	}

	int     num;
	char**  argv;
};
