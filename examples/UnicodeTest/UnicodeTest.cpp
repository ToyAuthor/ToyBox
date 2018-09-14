
#include <toy/Standard.hpp>

static int main2()
{
	toy::Log(u8"ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा\n");
	toy::Log( L"ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा\n");

	std::string    utf8 = u8"おもちゃ箱;";
	std::wstring   wide = toy::utf::UTF8ToWChar(utf8);

	toy::Logger<<u8"ToyBox;玩具箱;"<<wide<<u8"장난감 상자;"<<L"खिलौनो का बक्सा"<<toy::NewLine;

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
