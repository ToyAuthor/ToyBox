#include <string>
#include <cstdlib>
#include <toy/Log.hpp>
#include <toy/io/Reader.hpp>

int main2()
{
	toy::io::Reader<>   dev("text.txt");

	std::string   str;

	while ( dev.nextLine(&str) )
	{
		toy::Logger<<str<<toy::NewLine;
	}

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
