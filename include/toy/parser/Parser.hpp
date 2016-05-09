
#pragma once

#include <fstream>
#include "toy/Standard.hpp"


namespace toy{


class Parser
{
	public:
		Parser(){}
		Parser(std::string filename){LoadText(filename);}
		~Parser(){}

		void    LoadText(std::string filename);
		bool    NextLine(std::string &str);
		int     GetLineNumber();

	private:

		int             mLineNumber =0;
		std::ifstream   mFile;
};

}
