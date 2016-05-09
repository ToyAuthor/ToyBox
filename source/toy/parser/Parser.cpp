#include "toy/parser/Parser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


// Following warning will be output, if you don't define it.
// warning: 'boost::system::generic_category' defined but not used
#ifndef BOOST_SYSTEM_NO_DEPRECATED
#define BOOST_SYSTEM_NO_DEPRECATED 1
#endif

#include "boost/filesystem.hpp"


using namespace toy;


void Parser::LoadText(std::string filename)
{
	if ( !boost::filesystem::exists( filename ) )
	{
		// Can't find my file!
		toy::Oops(TOY_MARK);
		return;
	}

	mFile.close();
	mFile.open(filename.c_str(),std::ifstream::in);

	mLineNumber=0;


	//boost::filesystem::path   p1( filename.s() );
	//std::cout << "p1=" << p1 << "\n" << std::endl;
	//std::cout << "p1.name=" << p1.filename() << "\n" << std::endl;
}

/*
bool GetWord(std::string &str)
{
	while(getline(mFile,line))
	{
		cout << line << endl;
		istringstream ss(line);
		string word;

		while(ss >> word)
		{
			cout << word << endl;
		}

		cout << endl;
	}
}*/

bool Parser::NextLine(std::string &str)
{
	mLineNumber++;

	if(std::getline(mFile,str))
		return (bool)1;
	else
		return (bool)0;  // return 0, if no next line.
}

int Parser::GetLineNumber()
{
	return mLineNumber;
}
