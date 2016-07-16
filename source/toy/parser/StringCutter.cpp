#include "toy/parser/StringCutter.hpp"


using namespace toy;
using namespace parser;

StringCutter::StringCutter()
{
	;
}

StringCutter::~StringCutter()
{
	;
}

void StringCutter::loadString(std::string &str)
{
	_string = str;
	_index=0;
}

bool StringCutter::nextWord(std::string *_str)
{
	auto&   str = *_str;
	auto    latest_stack = _configStack.back();

	auto&   desireWord      = latest_stack->desireWord;
	auto&   ignore          = latest_stack->ignoreCharList.array;
	auto&   breakChar       = latest_stack->breakCharList.array;
	auto&   breakDoubleChar = latest_stack->breakDoubleCharList.array;

	auto&   i = _index;

	auto    get_size = [this]() -> decltype(_index)
	{
		return static_cast<decltype(_index)>(_string.size());
	};

	if ( i==get_size() )
	{
		return 0;
	}

	str.clear();


	if ( ! desireWord.empty() )
	{
		for(;;i++)
		{
			if ( i==get_size() )
			{
				return 0;
			}

			if ( desireWord.front()==_string[i] )
			{
				if ( desireWord.size() <= (_string.size()-i) )
				{
					if ( desireWord==std::string(_string,i,desireWord.size()) )
					{
						i+=desireWord.size();
						str+=desireWord;
						return 1;
					}
				}
				else
				{
					return 0;
				}
			}
		}
	}

	int     keep_loop = 1;

	for ( ; keep_loop ; i++ )
	{
		if ( i==get_size() )
		{
			return 0;
		}

		keep_loop=0;

		for ( int j = ignore.size()-1 ; j>=0 ; j-- )
		{
			if ( ignore[j] == _string[i])
			{
				keep_loop=1;
				break;
			}
		}
	}

	i--;

	if ( i+1 < get_size() )
	{
		for ( int j = breakDoubleChar.size()-1 ; j>=0 ; j-- )
		{
			if ( _string[i]  ==breakDoubleChar[j].t[0] &&
			     _string[i+1]==breakDoubleChar[j].t[1] )
			{
				str.push_back(breakDoubleChar[j].t[0]);
				str.push_back(breakDoubleChar[j].t[1]);
				i+=2;
				return 1;
			}
		}
	}

	if ( i < get_size() )
	{
		for ( int j = breakChar.size()-1 ; j>=0 ; j-- )
		{
			if ( _string[i] == breakChar[j] )
			{
				str.push_back(_string[i]);
				i++;
				return 1;
			}
		}
	}

	for (;; i++ )
	{
		if ( i==get_size() )
		{
			return 1;
		}

		for ( int j = ignore.size()-1 ; j>=0 ; j-- )
		{
			if ( _string[i] == ignore[j] )
			{
				return 1;
			}
		}

		for ( int j = breakChar.size()-1 ; j>=0 ; j-- )
		{
			if ( _string[i] == breakChar[j] )
			{
				return 1;
			}
		}

		for ( int j=breakDoubleChar.size()-1 ; j>=0 ; j-- )
		{
			if ( _string[i] == breakDoubleChar[j].t[0] )
			{
				if ( i+1 < get_size() )
				{
					if ( _string[i+1] == breakDoubleChar[j].t[1] )
					{
						return 1;
					}
				}
			}
		}

		str.push_back(_string[i]);
	}

	toy::Oops(TOY_MARK);
	return 0;
}

void StringCutter::pushConfig(ConfigPtr ptr)
{
	_configStack.push_back(ptr);
}

void StringCutter::popConfig(int num)
{
	auto   size = static_cast<decltype(num)>(_configStack.size());

	if ( num == size )
	{
		toy::Oops(TOY_MARK);
	}

	for ( ; num>0 ; num-- )
	{
		_configStack.pop_back();
	}
}
