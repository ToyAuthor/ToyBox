
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

		void    LoadString(std::string &str);
		bool    NextWord(std::string &str);

		void    PushConfig(ConfigPtr);
		void    PopConfig(int number=1);

	private:

		std::string              mString;
		int                      mIndex;

		std::vector<ConfigPtr>         mConfigStack;
};



}//namespace parser
}//namespace toy
