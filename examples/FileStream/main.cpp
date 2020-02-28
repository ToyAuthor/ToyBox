#include <cstdlib>
#include <toy/Log.hpp>
#include <toy/io/Stream.hpp>
#include <toy/path/Status.hpp>

static std::string FileName = "rawdata";
static std::string FolderName = "temp/FileStream/";

static void ShowFile(const uint8_t *buffer)
{
	toy::Logger<<"buffer:{"<<buffer[0]<<","<<buffer[1]<<","<<buffer[2]<<","<<buffer[3]<<","<<buffer[4]<<"}"<<toy::NewLine;
}

static void MakeBasicFile()
{
	uint8_t   buffer[5] = {12,45,99,42,35};

	/*
	 * Overwrite the file, if it exist.
	 * Create new file, if nothing there.
	 */
	toy::io::Stream   dev(FolderName+"/"+FileName);

	dev.write(buffer,5);
}

static void ModifyBasicFile()
{
	uint8_t   buffer[5] = {1,2,3,4,5};

	toy::io::Stream   dev(FolderName+"/"+FileName);

	dev>>2;
	dev.write(buffer,2);   // Just modify two bytes.

	/*
	 * { 12, 45, 99, 42, 35 }
	 *         {  1,  2,  3,  4,  5 }
	 * { 12, 45,  1,  2, 35 }
	 */
}

static int main2()
{
	toy::path::Remove(FolderName);

	if ( !toy::path::MakeDir(FolderName) ) return EXIT_FAILURE;

	MakeBasicFile();
	ModifyBasicFile();

	toy::io::Stream   dev;

	if ( dev.open(FolderName+"/"+FileName,toy::READ_ONLY) )
	{
		toy::Logger<<"success"<<toy::NewLine;
	}
	else
	{
		toy::Logger<<"failed"<<toy::NewLine;
	}

	uint8_t   buffer[5];

	dev.read(buffer,5);

	ShowFile(buffer);

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
