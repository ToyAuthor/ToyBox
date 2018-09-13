#include "toy/parser/Analyzer.hpp"

using namespace toy;
using namespace parser;

Analyzer::Analyzer()
{
	;
}

Analyzer::~Analyzer()
{
	this->drop();
}

void Analyzer::drop()
{
	if ( _configStack.size()>0 )
	{
		_configStack.pop_back();

		if ( _configStack.size()>0 )
		{
			toy::Oops(TOY_MARK);
			this->popConfig(static_cast<int>(_configStack.size())-1);
			_configStack.pop_back();
		}
	}
}

void Analyzer::loadString(std::string &str)
{
	_string = str;
	_index=0;
}

void Analyzer::pushFront(std::string str)
{
	#if TOY_OPTION_CHECK
		if ( sizeof(std::string::size_type)>sizeof(decltype(_index)) )
		{
			if ( str.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	auto  ss = static_cast<decltype(_index)>(str.size());

	if ( ss>_index )
	{
		toy::Oops(TOY_MARK);
	}

	_index -= ss;
}

bool Analyzer::nextWord(std::string *_str)
{
	auto&   str = *_str;
	auto    latest_stack = _configStack.back();

	auto&   desireWord      = latest_stack->desireWord;
	auto&   ignore          = latest_stack->ignoreCharList.array;
	auto&   breakChar       = latest_stack->breakCharList.array;
	auto&   breakDoubleChar = latest_stack->breakDoubleCharList.array;
	auto&   breakTripleChar = latest_stack->breakTripleCharList.array;

	auto&   i = _index;

	#if TOY_OPTION_CHECK
		if ( sizeof(std::string::size_type)>=sizeof(decltype(_index)) )
		{
			if ( _string.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	auto  get_size = static_cast<decltype(_index)>(_string.size());

	if ( i>=get_size )
	{
		return 0;
	}

	str.clear();

	if ( ! desireWord.empty() )
	{
		for(;;i++)
		{
			if ( i>=get_size )
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

	for ( decltype(_index) keep_loop = 1 ; keep_loop ; i++ )
	{
		if ( i>=get_size )
		{
			return 0;
		}

		keep_loop=0;

		#if TOY_OPTION_CHECK
			if ( sizeof(std::string::size_type)>=sizeof(decltype(_index)) )
			{
				if ( ignore.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}
			}
		#endif

		for ( auto j = static_cast<decltype(_index)>(ignore.size()-1) ; j>=0 ; j-- )
		{
			if ( ignore[j] == _string[i])
			{
				keep_loop=1;
				break;
			}
		}
	}

	i--;

	if ( i+2 < get_size )
	{
		#if TOY_OPTION_CHECK
			if ( sizeof(std::string::size_type)>=sizeof(decltype(_index)) )
			{
				if ( breakTripleChar.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}
			}
		#endif

		for ( auto j = static_cast<decltype(_index)>(breakTripleChar.size()-1) ; j>=0 ; j-- )
		{
			if ( _string[i]  ==breakTripleChar[j].t[0] &&
			     _string[i+1]==breakTripleChar[j].t[1] &&
				 _string[i+2]==breakTripleChar[j].t[2] )
			{
				str.push_back(breakTripleChar[j].t[0]);
				str.push_back(breakTripleChar[j].t[1]);
				str.push_back(breakTripleChar[j].t[2]);
				i+=3;
				return 1;
			}
		}
	}

	if ( i+1 < get_size )
	{
		#if TOY_OPTION_CHECK
			if ( sizeof(std::string::size_type)>=sizeof(decltype(_index)) )
			{
				if ( breakDoubleChar.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}
			}
		#endif

		for ( auto j = static_cast<decltype(_index)>(breakDoubleChar.size()-1) ; j>=0 ; j-- )
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

	if ( i < get_size )
	{
		#if TOY_OPTION_CHECK
			if ( sizeof(std::string::size_type)>=sizeof(decltype(_index)) )
			{
				if ( breakChar.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}
			}
		#endif

		for ( auto j = static_cast<decltype(_index)>(breakChar.size()-1) ; j>=0 ; j-- )
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
		if ( i>=get_size )
		{
			return 1;
		}

		#if TOY_OPTION_CHECK
			if ( sizeof(std::string::size_type)>=sizeof(decltype(_index)) )
			{
				if ( ignore.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}

				if ( breakChar.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}

				if ( breakDoubleChar.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}

				if ( breakTripleChar.size() > static_cast<std::string::size_type>(std::numeric_limits<decltype(_index)>::max()) )
				{
					toy::Oops(TOY_MARK);
				}
			}
		#endif

		for ( auto j = static_cast<decltype(_index)>(ignore.size()-1) ; j>=0 ; j-- )
		{
			if ( _string[i] == ignore[j] )
			{
				return 1;
			}
		}

		for ( auto j = static_cast<decltype(_index)>(breakChar.size()-1) ; j>=0 ; j-- )
		{
			if ( _string[i] == breakChar[j] )
			{
				return 1;
			}
		}

		for ( auto j = static_cast<decltype(_index)>(breakDoubleChar.size()-1) ; j>=0 ; j-- )
		{
			if ( _string[i] == breakDoubleChar[j].t[0] )
			{
				if ( i+1 < get_size )
				{
					if ( _string[i+1] == breakDoubleChar[j].t[1] )
					{
						return 1;
					}
				}
			}
		}

		for ( auto j = static_cast<decltype(_index)>(breakTripleChar.size()-1) ; j>=0 ; j-- )
		{
			if ( _string[i] == breakTripleChar[j].t[0] )
			{
				if ( i+1 < get_size )
				{
					if ( _string[i+1] == breakTripleChar[j].t[1] )
					{
						if ( i+2 < get_size )
						{
							if ( _string[i+2] == breakTripleChar[j].t[2] )
							{
								return 1;
							}
						}
					}
				}
			}
		}

		str.push_back(_string[i]);
	}

	toy::Oops(TOY_MARK);
	return 0;
}

void Analyzer::pushConfig(ConfigPtr ptr)
{
	_configStack.push_back(ptr);
}

void Analyzer::popConfig(int num)
{
	#if TOY_OPTION_CHECK
		if ( sizeof(decltype(num)) > sizeof(std::string::size_type) )
		{
			if ( static_cast<decltype(num)>(_configStack.size()) <= num )
			{
				toy::Oops(TOY_MARK);
			}
		}
		else
		{
			if ( _configStack.size() <= static_cast<std::string::size_type>(num) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	for ( ; num>0 ; num-- )
	{
		_configStack.pop_back();
	}
}

auto Analyzer::getConfig()->ConfigPtr
{
	if ( _configStack.empty() )
	{
		return nullptr;
	}

	return _configStack.back();
}
