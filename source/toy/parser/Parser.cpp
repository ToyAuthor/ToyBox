#include "toy/parser/Parser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace toy;


void Parser::loadText(std::string filename)
{
	if ( !boost::filesystem::exists( filename ) )
	{
		// Can't find my file!
		toy::Oops(TOY_MARK);
		return;
	}

	_file.close();
	_file.open(filename,std::ifstream::in);

	_lineNumber=0;
}

bool Parser::nextLine(std::string *str)
{
	if ( ! _file.good() )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

	_lineNumber++;

	if ( std::getline(_file,*str) )
	{
		return 1;
	}
	else
	{
		return 0;  // return 0, if no next line.
	}
}

int Parser::getLineNumber()
{
	return _lineNumber;
}
