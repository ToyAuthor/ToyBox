#include <cstdlib>
#include <toy/Log.hpp>
#include <toy/Photo.hpp>
#include <toy_example/File.hpp>

static int main2()
{
	toy::path::Remove("temp/ArchiveStream");

	if ( !toy::path::MakeDir("temp/ArchiveStream") ) return EXIT_FAILURE;

	toy::ImageBuffer   buffer;

	if ( ! toy::example::LoadImage(std::string(TOY_RESOURCE_PATH)+"/package.7z",u8"大阪城.bmp",&buffer,toy::SEVEN_ZIP) )
	{
		toy::Oops(TOY_MARK);
		return EXIT_FAILURE;
	}

	toy::photo::UpsideDown(&buffer);
	toy::file::loader::png::Save("temp/ArchiveStream/image.png",&buffer);

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
