#include "toy/parser/Dictionary.hpp"


using namespace toy;
using namespace parser;


bool Dictionary::isExist(std::string key)
{
	if ( _tree.find(key) == _tree.end() )
	{
		return 0;
	}

	return 1;
}

void Dictionary::setKeyValue(std::string key,std::function<void(void)> value)
{
	if( isExist(key) )
	{
		// You can't insert a same key.
		toy::Oops(TOY_MARK);
	}
	else
	{
		_tree[key]=value;
	}
}
