
#pragma once

#include "toy/Standard.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{

class Dictionary;

class TOY_API_PARSER Translator
{
	public:

		typedef std::shared_ptr<Dictionary> DictionaryPtr;

		Translator();
		~Translator();

		bool    isExist(std::string key);
		void    transle(std::string key);
		void    publishNextLine();
		void    publishUnknown(std::string key);
		void    pushDictionary(DictionaryPtr);
		void    popDictionary(int number=1);
		void    drop();

		DictionaryPtr getDictionary();

	private:

		std::vector<DictionaryPtr>      _data;
};

}//namespace parser
}//namespace toy
