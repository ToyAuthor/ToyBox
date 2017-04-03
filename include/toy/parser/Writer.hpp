
#pragma once

#include <fstream>
#include "toy/Standard.hpp"

namespace toy{
namespace parser{

class Writer
{
	public:

		Writer(){}
		Writer(std::string filename){open(filename);}
		~Writer(){}

		bool open(std::string filename)
		{
			if ( boost::filesystem::exists( filename ) )
			{
				// No! Always open new one. Always!
				toy::Oops(TOY_MARK);
				return false;
			}

			_file.open(filename);

			return true;
		}

		void nextLine()
		{
			_file<<std::endl;
		}

		void print(std::string str)
		{
			_file<<str<<std::endl;
		}

		void printf(std::string str)
		{
			_file<<str;
		}

	private:

		std::ofstream   _file;
};

}
}
