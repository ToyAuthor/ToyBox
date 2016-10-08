#include "toy/parser/Reader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace toy;
using namespace parser;


bool Reader::open(std::string filename)
{
	if ( !boost::filesystem::exists( filename ) )
	{
		// Can't find my file!
		toy::Oops(TOY_MARK);
		return false;
	}

	_file.close();
	_file.open(filename,std::ifstream::in);

	_lineNumber = false;
	return true;
}

bool Reader::nextLine(std::string *str)
{
	if ( ! _file.good() )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

//	if ( std::getline(_file,*str,'\n') )
	if ( std::getline(_file,*str) )
	{
		_lineNumber++;
		return 1;
	}
	else
	{
		return 0;  // return 0, if no next line.
	}
}

int Reader::getLineNumber()
{
	return _lineNumber;
}
