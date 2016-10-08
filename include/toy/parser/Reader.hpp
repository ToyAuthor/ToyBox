
#pragma once

#include <fstream>
#include "toy/Standard.hpp"


namespace toy{
namespace parser{

class TOY_API Reader
{
	public:

		Reader(){}
		Reader(std::string filename){open(filename);}
		~Reader(){}

		bool    open(std::string filename);
		bool    nextLine(std::string *str);
		int     getLineNumber();

	private:

		int             _lineNumber =0;
		std::ifstream   _file;
};

}
}
