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

void StringCutter::LoadString(std::string &str)
{
	mString=str;
	mIndex=0;
}

bool StringCutter::NextWord(std::string &str)
{
	auto    latest_stack = mConfigStack.back();

	auto&   desireWord      = latest_stack->desireWord;
	auto&   ignore          = latest_stack->ignoreCharList.array;
	auto&   breakChar       = latest_stack->breakCharList.array;
	auto&   breakDoubleChar = latest_stack->breakDoubleCharList.array;

	if(mIndex==static_cast<decltype(mIndex)>(mString.size()))
	{
		return 0;
	}

	str.clear();

	int  &i=mIndex;

	if( ! desireWord.empty() )
	{
		for(;;i++)
		{
			if(i==static_cast<decltype(mIndex)>(mString.size()))
			{
				return 0;
			}

			if( desireWord.front()==mString[i] )
			{
				if( desireWord.size() <= (mString.size()-i) )
				{
					if( desireWord==std::string(mString,i,desireWord.size()) )
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

	int  keep_loop=1;

	for(;keep_loop;i++)
	{
		if(i==static_cast<decltype(mIndex)>(mString.size()))
		{
			return 0;
		}

		keep_loop=0;

		for(int j=ignore.size()-1; j>=0 ;j--)
		{
			if(ignore[j] == mString[i])
			{
				keep_loop=1;
				break;
			}
		}
	}

	i--;

	if( i+1 < static_cast<decltype(mIndex)>(mString.size()) )
	{
		for(int j=breakDoubleChar.size()-1; j>=0 ;j--)
		{
			if( mString[i]  ==breakDoubleChar[j].t[0] &&
			    mString[i+1]==breakDoubleChar[j].t[1] )
			{
				str.push_back(breakDoubleChar[j].t[0]);
				str.push_back(breakDoubleChar[j].t[1]);
				i+=2;
				return 1;
			}
		}
	}

	if( i < static_cast<decltype(mIndex)>(mString.size()) )
	{
		for(int j=breakChar.size()-1; j>=0 ;j--)
		{
			if( mString[i] == breakChar[j] )
			{
				str.push_back(mString[i]);
				i++;
				return 1;
			}
		}
	}

	for(;;i++)
	{
		if(i==static_cast<decltype(mIndex)>(mString.size()))
		{
			return 1;
		}

		for(int j=ignore.size()-1; j>=0 ;j--)
		{
			if(mString[i] == ignore[j])
			{
				return 1;
			}
		}

		for(int j=breakChar.size()-1; j>=0 ;j--)
		{
			if(mString[i] == breakChar[j])
			{
				return 1;
			}
		}

		for(int j=breakDoubleChar.size()-1; j>=0 ;j--)
		{
			if(mString[i] == breakDoubleChar[j].t[0])
			{
				if(i+1<static_cast<decltype(mIndex)>(mString.size()))
				{
					if(mString[i+1] == breakDoubleChar[j].t[1])
					{
						return 1;
					}
				}
			}
		}

		str.push_back(mString[i]);
	}

	toy::Oops(TOY_MARK);
	return 0;
}

void StringCutter::PushConfig(ConfigPtr ptr)
{
	mConfigStack.push_back(ptr);
}

void StringCutter::PopConfig(int num)
{
	if( num == static_cast<decltype(num)>(mConfigStack.size()) )
	{
		toy::Oops(TOY_MARK);
	}

	for(;num>0;num--)
	{
		mConfigStack.pop_back();
	}
}
