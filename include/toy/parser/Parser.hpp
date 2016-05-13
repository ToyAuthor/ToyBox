
#pragma once

#include <fstream>
#include "toy/Standard.hpp"


namespace toy{

class Parser
{
	public:

		Parser(){}
		Parser(std::string filename){loadText(filename);}
		~Parser(){}

		void    loadText(std::string filename);
		bool    nextLine(std::string *str);
		int     getLineNumber();

	private:

		int             _lineNumber =0;
		std::ifstream   _file;
};

}
