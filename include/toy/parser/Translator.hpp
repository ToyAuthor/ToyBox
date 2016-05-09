
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace parser{


class Translator
{
	public:

		class Dictionary
		{
			friend class Translator;

			public:

				Dictionary()
				{
					CallbackNextLine = std::bind(&Dictionary::EmptyFunction1,this);
					CallbackUnknown  = std::bind(&Dictionary::EmptyFunction2,this,std::placeholders::_1);
				}

				~Dictionary(){}

				std::function<void(void)>                CallbackNextLine;
				std::function<void(std::string key)>     CallbackUnknown;

				void SetKeyValue(std::string key,std::function<void(void)> value);

			private:

				void EmptyFunction1(){}
				void EmptyFunction2(std::string){}

				bool IsExist(std::string key);
				std::map<std::string,std::function<void(void)> >     mTree;
		};

		typedef std::shared_ptr<Dictionary> DictionaryPtr;

		Translator();
		~Translator();

		bool    IsExist(std::string key);
		void    Transle(std::string key);
		void    PublishNextLine();
		void    PublishUnknown(std::string key);
		void    PushDictionary(DictionaryPtr);
		void    PopDictionary(int number=1);

		DictionaryPtr GetDictionary();

	private:

		std::vector<DictionaryPtr>      mDictionaryStack;
};

}//namespace parser
}//namespace toy
