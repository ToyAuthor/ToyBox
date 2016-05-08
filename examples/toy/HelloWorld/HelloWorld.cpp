
#include <cstdlib>
#include "toy/Root.hpp"


int main2()
{
	toy::Log("Hello world\n");
	toy::Log("哈囉\n");

	toy::Root               root;                   // Please declare it before any object of ToyBox.

	return EXIT_SUCCESS;
}

int main()
{
	int result = EXIT_FAILURE;

	try
	{
		result = main2();
	}
	catch(toy::Exception &e)
	{
		toy::Log(e);
	}

	return result;
}
