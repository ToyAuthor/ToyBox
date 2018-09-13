#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <toy/ProcArg.hpp>

template<typename T>
static void PrintContent(std::string tag,T ptr)
{
	if ( ptr )
	{
		std::cout<<"tag:"<<tag<<std::endl;

		if ( ptr->size()>0 )
		{
			for ( auto &x : *ptr )
			{
				std::cout<<x<<std::endl;
			}
		}
		else
		{
			std::cout<<"no content"<<std::endl;
		}
	}
	else
	{
		std::cout<<"no such tag named:"<<tag<<std::endl;
	}
}

// $ *.exe option1 -p option2
// $ tag:non
// $ option1
// $ tag:-p
// $ option2
// $
// $ *.exe option1 option2 -p option3 option4
// $ tag:non
// $ option1
// $ option2
// $ tag:-p
// $ option3
// $ option4
// $
// $ *.exe option1 option2 option3 option4
// $ tag:non
// $ option1
// $ option2
// $ option3
// $ option4
// $ no such tag named:-p
// $
// $ *.exe -p option1 option2 option3 option4
// $ no such tag named:non
// $ tag:-p
// $ option1
// $ option2
// $ option3
// $ option4
// $
// $ *.exe -p
// $ no such tag named:non
// $ tag:-p
// $ no content
// $
// $ *.exe
// $ no such tag named:non
// $ no such tag named:-p
int main2(int argc, char** argv)
{
	toy::ProcArg  arg(argc,argv);

	const auto  np = arg[""];

	PrintContent("non",np);

	const auto  sp = arg["-p"];

	PrintContent("-p",sp);

	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	int result = EXIT_FAILURE;

	try
	{
		result = main2(argc,argv);
	}
	catch(std::exception &e)
	{
		std::cout<<e.what()<<std::endl;
	}

	return result;
}
