#include <string>
#include <cstdlib>
#include <toy/Log.hpp>
#include <toy/io/Reader.hpp>

static void PrintTextFileContent(std::string fileName)
{
	toy::io::Reader<>   dev(fileName);

	std::string   buffer;

	while ( dev.nextLine(&buffer) )
	{
		toy::Logger<<buffer<<toy::NewLine;
	}
}

int main()
{
	PrintTextFileContent("text.txt");

	return EXIT_SUCCESS;
}
