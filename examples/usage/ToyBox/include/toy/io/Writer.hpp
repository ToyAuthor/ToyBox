#include <string>
#include <cstdlib>
#include <toy/Log.hpp>
#include <toy/io/Writer.hpp>

// Output file look like this
/*
line 1
line 2
line 3
*/

static void SaveToTextFile(std::string fileName)
{
	toy::io::Writer<>   dev(fileName);

	// "Writer::print" == "Writer::printf" + "Writer::newLine"
	dev.print( "line 1");
	dev.printf("line 2");  dev.newLine();
	dev.print( "line 3");
}

int main()
{
	SaveToTextFile("text.txt");

	return EXIT_SUCCESS;
}
