
#pragma once

#include "toy/parser/StringCutterConfig.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{


// Take string apart by given rule. You can call it analyzer.
class TOY_API_PARSER StringCutter
{
	public:

		typedef std::shared_ptr<StringCutterConfig> ConfigPtr;

		StringCutter();
		~StringCutter();

		void    loadString(std::string &str);
		bool    nextWord(std::string *str);    // Next token

		void    pushConfig(ConfigPtr);
		void    popConfig(int number=1);
		auto    getConfig()->ConfigPtr;
		void    pushFront(std::string str);
		void    drop();

	private:

		std::string              _string;
		int                      _index = 0;

		std::vector<ConfigPtr>   _configStack;
};



}//namespace parser
}//namespace toy
