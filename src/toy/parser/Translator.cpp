#include "toy/parser/Translator.hpp"
#include "toy/parser/Dictionary.hpp"

using namespace toy;
using namespace parser;


Translator::Translator()
{
	;
}

Translator::~Translator()
{
	this->drop();
}

void Translator::drop()
{
	if ( _data.size()>0 )
	{
		_data.pop_back();

		if ( _data.size()>0 )
		{
			toy::Oops(TOY_MARK);
			popDictionary(static_cast<int>(_data.size())-1);
			_data.pop_back();
		}
	}
}

bool Translator::isExist(std::string key)
{
	return _data.back()->isExist(key);
}

void Translator::transle(std::string key)
{
	auto  ptr = _data.back();
	ptr->callbackKnown(key);
	_data.back()->_tree[key]();
}

void Translator::publishNextLine()
{
	_data.back()->callbackNextLine();
}

void Translator::publishUnknown(std::string key)
{
	auto  ptr = _data.back();
	ptr->callbackUnknown(key);
}

void Translator::pushDictionary(DictionaryPtr ptr)
{
	_data.push_back(ptr);
}

void Translator::popDictionary(int num)
{
	auto   size = static_cast<decltype(num)>(_data.size());

	if ( num == size )
	{
		// Don't clean all.
		toy::Oops(TOY_MARK);
	}

	for (; num>0 ; num-- )
	{
		_data.pop_back();
	}
}

Translator::DictionaryPtr Translator::getDictionary()
{
	if ( _data.empty() )
	{
		return nullptr;
	}

	return _data.back();
}
