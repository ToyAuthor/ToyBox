#pragma once

#include "toy/Standard.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{


class Translator;

class TOY_API_PARSER Dictionary
{
	friend class Translator;

	public:

		Dictionary(){}
		~Dictionary(){}

		std::function<void(void)>            callbackNextLine = [](){};
		std::function<void(std::string)>     callbackUnknown = [](std::string){};
		std::function<void(std::string)>     callbackKnown = [](std::string){};

		void setKeyValue(std::string key,std::function<void(void)> value);

	private:

		bool isExist(std::string key);
		std::map<std::string,std::function<void(void)> >     _tree;
};

inline std::shared_ptr<toy::parser::Dictionary> NewDictionary()
{
	return std::make_shared<toy::parser::Dictionary>();
}


}//namespace parser
}//namespace toy
