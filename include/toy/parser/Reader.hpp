
#pragma once

#include <fstream>
#include "toy/Standard.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{

class TOY_API_PARSER Reader
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
