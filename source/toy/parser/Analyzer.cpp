#include <algorithm>
#include "toy/math/SafeInt.hpp"
#include "toy/parser/Analyzer.hpp"

static void ReverseString(std::string *str)
{
	if ( ! str->empty() )
	{
		std::reverse(str->begin(), str->end());
	}
}

namespace toy{
namespace parser{

class _AnalyzerBuffer
{
	public:

		_AnalyzerBuffer()
		{
			;
		}

		virtual ~_AnalyzerBuffer()
		{
			;
		}

		void reset(const std::string& str)
		{
			_buffer = str;
			_index = 0;
		}

		virtual void forward(uint32_t offset)=0;
		virtual void backward(uint32_t offset)=0;
		virtual bool nextWord(std::string *str,std::shared_ptr<AnalyzerConfig> ptr)=0;

	protected:

		std::string                       _buffer;
		std::string::size_type            _index = 0;
};

class _AnalyzerBufferRight : public _AnalyzerBuffer
{
	public:

		_AnalyzerBufferRight(const std::string& str)
		{
			_buffer = str;
		}

		~_AnalyzerBufferRight()
		{
			;
		}

		bool nextWord(std::string *str,std::shared_ptr<AnalyzerConfig> ptr);

		void forward(uint32_t offset)
		{
			(void)offset;
		}

		void backward(uint32_t offset)
		{
			(void)offset;
		}
};

class _AnalyzerBufferLeft : public _AnalyzerBuffer
{
	public:

		_AnalyzerBufferLeft(const std::string& str)
		{
			_buffer = str;
			_index = str.size();
		}

		~_AnalyzerBufferLeft()
		{
			;
		}

		bool nextWord(std::string *str,std::shared_ptr<AnalyzerConfig> ptr);

		void forward(uint32_t offset)
		{
			(void)offset;
		}

		void backward(uint32_t offset)
		{
			(void)offset;
		}
};

bool _AnalyzerBufferRight::nextWord(std::string *strPtr,std::shared_ptr<AnalyzerConfig> latest_stack)
{
	auto&   str = *strPtr;
	auto&   desireWord      = latest_stack->desireWord;
	auto&   ignore          = latest_stack->ignoreCharList._getRef();
	auto&   breakChar       = latest_stack->breakCharList._getRef();
	auto&   breakDoubleChar = latest_stack->breakDoubleCharList._getRef();
	auto&   breakTripleChar = latest_stack->breakTripleCharList._getRef();

	str.clear();

	const auto total = _buffer.size();

	if ( ! desireWord.empty() )
	{
		for(;;_index++)
		{
			if ( _index>=total )
			{
				return false;
			}

			if ( desireWord.front()==_buffer[_index] )
			{
				if ( desireWord.size() <= (total-_index) )
				{
					if ( desireWord==std::string(_buffer,_index,desireWord.size()) )
					{
						_index+=desireWord.size();
						str+=desireWord;
						return true;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}

	for ( bool keep_loop = true ; keep_loop ; _index++ )
	{
		if ( _index>=total )
		{
			return false;
		}

		keep_loop = false;

		for ( auto j = ignore.size() ; j>0 ; j-- )
		{
			if ( ignore[j-1] == _buffer[_index])
			{
				keep_loop = true;
				break;
			}
		}
	}

	_index--;

	if ( _index+2 < total )
	{
		for ( auto j = breakTripleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index]  ==breakTripleChar[j-1].t[0] &&
			     _buffer[_index+1]==breakTripleChar[j-1].t[1] &&
				 _buffer[_index+2]==breakTripleChar[j-1].t[2] )
			{
				str.push_back(breakTripleChar[j-1].t[0]);
				str.push_back(breakTripleChar[j-1].t[1]);
				str.push_back(breakTripleChar[j-1].t[2]);
				_index += 3;

				return true;
			}
		}
	}

	if ( _index+1 < total )
	{
		for ( auto j = breakDoubleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index]  ==breakDoubleChar[j-1].t[0] &&
			     _buffer[_index+1]==breakDoubleChar[j-1].t[1] )
			{
				str.push_back(breakDoubleChar[j-1].t[0]);
				str.push_back(breakDoubleChar[j-1].t[1]);
				_index += 2;

				return true;
			}
		}
	}

	if ( _index < total )
	{
		for ( auto j = breakChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index] == breakChar[j-1] )
			{
				str.push_back(_buffer[_index]);
				_index++;
				return true;
			}
		}
	}

	for ( ;; _index++ )
	{
		if ( _index>=total )
		{
			return true;
		}

		for ( auto j = ignore.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index] == ignore[j-1] )
			{
				return true;
			}
		}

		for ( auto j = breakChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index] == breakChar[j-1] )
			{
				return true;
			}
		}

		for ( auto j = breakDoubleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index] == breakDoubleChar[j-1].t[0] )
			{
				if ( _index+1 < total )
				{
					if ( _buffer[_index+1] == breakDoubleChar[j-1].t[1] )
					{
						return true;
					}
				}
			}
		}

		for ( auto j = breakTripleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index] == breakTripleChar[j-1].t[0] )
			{
				if ( _index+1 < total )
				{
					if ( _buffer[_index+1] == breakTripleChar[j-1].t[1] )
					{
						if ( _index+2 < total )
						{
							if ( _buffer[_index+2] == breakTripleChar[j-1].t[2] )
							{
								return true;
							}
						}
					}
				}
			}
		}

		str.push_back(_buffer[_index]);
	}

	toy::Oops(TOY_MARK);
	return false;
}

bool _AnalyzerBufferLeft::nextWord(std::string *strPtr,std::shared_ptr<AnalyzerConfig> latest_stack)
{
	auto&   str = *strPtr;
	auto&   desireWord      = latest_stack->desireWord;
	auto&   ignore          = latest_stack->ignoreCharList._getRef();
	auto&   breakChar       = latest_stack->breakCharList._getRef();
	auto&   breakDoubleChar = latest_stack->breakDoubleCharList._getRef();
	auto&   breakTripleChar = latest_stack->breakTripleCharList._getRef();

	(void)ignore;
	(void)breakChar;
	(void)breakDoubleChar;
	(void)breakTripleChar;

	str.clear();

	const auto total = _buffer.size();
	(void)total;

	if ( ! desireWord.empty() )
	{
		for(;;_index--)
		{
			if ( _index==0 )
			{
				return false;
			}

			if ( desireWord.back()==_buffer[_index-1] )
			{
				if ( desireWord.size() <= _index )
				{
					if ( desireWord==std::string(_buffer,_index-desireWord.size(),desireWord.size()) )
					{
						_index -= desireWord.size();
						str += desireWord;
						return true;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}

	for ( bool keep_loop = true ; keep_loop ; _index-- )
	{
		if ( _index==0 )
		{
			return false;
		}

		keep_loop = false;

		for ( auto j = ignore.size() ; j>0 ; j-- )
		{
			if ( ignore[j-1] == _buffer[_index-1])
			{
				keep_loop = true;
				break;
			}
		}
	}

	_index++;

	if ( _index>2 )
	{
		for ( auto j = breakTripleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-3] == breakTripleChar[j-1].t[0] &&
			     _buffer[_index-2] == breakTripleChar[j-1].t[1] &&
				 _buffer[_index-1] == breakTripleChar[j-1].t[2] )
			{
				str.push_back(breakTripleChar[j-1].t[0]);
				str.push_back(breakTripleChar[j-1].t[1]);
				str.push_back(breakTripleChar[j-1].t[2]);
				_index -= 3;

				return true;
			}
		}
	}

	if ( _index>1 )
	{
		for ( auto j = breakDoubleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-2] == breakDoubleChar[j-1].t[0] &&
			     _buffer[_index-1] == breakDoubleChar[j-1].t[1] )
			{
				str.push_back(breakDoubleChar[j-1].t[0]);
				str.push_back(breakDoubleChar[j-1].t[1]);
				_index -= 2;

				return true;
			}
		}
	}

	if ( _index>0 )
	{
		for ( auto j = breakChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-1] == breakChar[j-1] )
			{
				str.push_back(_buffer[_index-1]);
				_index--;
				return true;
			}
		}
	}

	for ( ;; _index-- )
	{
		if ( _index==0 )
		{
			ReverseString(strPtr);
			return true;
		}

		for ( auto j = ignore.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-1] == ignore[j-1] )
			{
				ReverseString(strPtr);
				return true;
			}
		}

		for ( auto j = breakChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-1] == breakChar[j-1] )
			{
				ReverseString(strPtr);
				return true;
			}
		}

		for ( auto j = breakDoubleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-1] == breakDoubleChar[j-1].t[1] )
			{
				if ( _index>1 )
				{
					if ( _buffer[_index-2] == breakDoubleChar[j-1].t[0] )
					{
						ReverseString(strPtr);
						return true;
					}
				}
			}
		}

		for ( auto j = breakTripleChar.size() ; j>0 ; j-- )
		{
			if ( _buffer[_index-1] == breakTripleChar[j-1].t[2] )
			{
				if ( _index>1 )
				{
					if ( _buffer[_index-2] == breakTripleChar[j-1].t[1] )
					{
						if ( _index+2 < total )
						{
							if ( _buffer[_index-3] == breakTripleChar[j-1].t[0] )
							{
								ReverseString(strPtr);
								return true;
							}
						}
					}
				}
			}
		}

		str.push_back(_buffer[_index-1]);
	}

	toy::Oops(TOY_MARK);
	return true;
}

}}

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

void Analyzer::loadString(const std::string &str,enum toy::Option option)
{
	if ( option == _option )
	{
		_buffer->reset(str);
		return;
	}

	if ( option==toy::RIGHTWARD )
	{
		_buffer.reset(new _AnalyzerBufferRight(str));
	}
	else if ( option==toy::LEFTWARD )
	{
		_buffer.reset(new _AnalyzerBufferLeft(str));
	}
	else
	{
		toy::Oops(TOY_MARK);
		_buffer.reset(new _AnalyzerBufferRight(str));
	}

	_option = option;
}

void Analyzer::pushFront(const std::string &str)
{
	_buffer->backward(toy::math::SafeInt<uint32_t>(str.size(),TOY_MARK));
}

bool Analyzer::nextWord(std::string *_str)
{
	return _buffer->nextWord(_str,_configStack.back());
}

/*
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
		return false;
	}

	str.clear();

	if ( ! desireWord.empty() )
	{
		for(;;i++)
		{
			if ( i>=get_size )
			{
				return false;
			}

			if ( desireWord.front()==_string[i] )
			{
				if ( desireWord.size() <= (_string.size()-i) )
				{
					if ( desireWord==std::string(_string,i,desireWord.size()) )
					{
						i+=desireWord.size();
						str+=desireWord;
						return true;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}

	for ( decltype(_index) keep_loop = 1 ; keep_loop ; i++ )
	{
		if ( i>=get_size )
		{
			return false;
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
				return true;
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
				return true;
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
				return true;
			}
		}
	}

	for (;; i++ )
	{
		if ( i>=get_size )
		{
			return true;
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
				return true;
			}
		}

		for ( auto j = static_cast<decltype(_index)>(breakChar.size()-1) ; j>=0 ; j-- )
		{
			if ( _string[i] == breakChar[j] )
			{
				return true;
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
						return true;
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
								return true;
							}
						}
					}
				}
			}
		}

		str.push_back(_string[i]);
	}

	toy::Oops(TOY_MARK);
	return false;
}*/

void Analyzer::pushConfig(std::shared_ptr<AnalyzerConfig> ptr)
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

auto Analyzer::getConfig()->std::shared_ptr<AnalyzerConfig>
{
	if ( _configStack.empty() )
	{
		return nullptr;
	}

	return _configStack.back();
}
