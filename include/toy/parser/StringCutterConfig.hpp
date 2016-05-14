
#pragma once

#include "toy/Standard.hpp"


namespace toy{
namespace parser{

class TOY_API StringCutterConfig
{
	public:

		struct CChar
		{
			CChar(char c1,char c2)
			{
				t[0]=c1;
				t[1]=c2;
			}
			CChar()
			{
				t[0]='b';
				t[1]='t';
			}
			char  t[2];
		};

		template<typename T>
		class List
		{
			friend class StringCutter;

			public:

				List(){}
				~List(){}

				void push(T stack)
				{
					array.push_back(stack);
				}

				void pop()
				{
					array.pop_back();
				}

			private:

				std::vector<T>    array;
		};

		StringCutterConfig();
		~StringCutterConfig();

		void    useDefault();

		List<char>    breakCharList;
		List<CChar>   breakDoubleCharList;
		List<char>    ignoreCharList;
		std::string   desireWord;
};

}//namespace parser
}//namespace toy
