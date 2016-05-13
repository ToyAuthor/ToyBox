#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace parser{


class Translator;

class Dictionary
{
	friend class Translator;

	public:

		Dictionary(){}
		~Dictionary(){}

		std::function<void(void)>            callbackNextLine = [](){};
		std::function<void(std::string)>     callbackUnknown = [](std::string){};

		void setKeyValue(std::string key,std::function<void(void)> value);

	private:

		bool isExist(std::string key);
		std::map<std::string,std::function<void(void)> >     _tree;
};


}//namespace parser
}//namespace toy
