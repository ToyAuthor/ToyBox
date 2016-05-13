
#pragma once

#include "toy/parser/StringCutterConfig.hpp"

namespace toy{
namespace parser{


// Take string apart by given rule.
class StringCutter
{
	public:

		typedef std::shared_ptr<StringCutterConfig> ConfigPtr;

		StringCutter();
		~StringCutter();

		void    loadString(std::string &str);
		bool    nextWord(std::string &str);

		void    pushConfig(ConfigPtr);
		void    popConfig(int number=1);

	private:

		std::string              _string;
		int                      _index = 0;

		std::vector<ConfigPtr>   _configStack;
};



}//namespace parser
}//namespace toy
