
#include <cstdlib>
#include "toy/Root.hpp"


int main2()
{
	toy::Log("Hello world\n");
	toy::Log("哈囉\n");

	toy::Root      root;

	return EXIT_SUCCESS;
}

int main()
{
	int result = EXIT_FAILURE;

	try
	{
		result = main2();
	}
	catch(std::exception &e)
	{
		toy::Log(e);
	}

	return result;
}
