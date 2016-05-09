#include "toy/parser/Translator.hpp"


using namespace toy;
using namespace parser;


Translator::Translator()
{
	;
}

Translator::~Translator()
{
	;
}

bool Translator::IsExist(std::string key)
{
	return mDictionaryStack.back()->IsExist(key);
}

void Translator::Transle(std::string key)
{
	mDictionaryStack.back()->mTree[key]();
}

void Translator::PublishNextLine()
{
	mDictionaryStack.back()->CallbackNextLine();
}

void Translator::PublishUnknown(std::string key)
{
	auto  ptr = mDictionaryStack.back();
	ptr->CallbackUnknown(key);
}

void Translator::PushDictionary(DictionaryPtr ptr)
{
	mDictionaryStack.push_back(ptr);
}

void Translator::PopDictionary(int num)
{
	if( num == static_cast<decltype(num)>(mDictionaryStack.size()) )
	{
		// Don't clean all.
		toy::Oops(TOY_MARK);
	}

	for(;num>0;num--)
	{
		mDictionaryStack.pop_back();
	}
}

Translator::DictionaryPtr Translator::GetDictionary()
{
	return mDictionaryStack.back();
}

//------------------------------------------------------------------------------

bool Translator::Dictionary::IsExist(std::string key)
{
	if(mTree.find(key) == mTree.end())
	{
		return 0;
	}

	return 1;
}

void Translator::Dictionary::SetKeyValue(std::string key,std::function<void(void)> value)
{
	if( IsExist(key) )
	{
		// You can't insert a same key.
		toy::Oops(TOY_MARK);
	}
	else
	{
		mTree[key]=value;
	}
}
