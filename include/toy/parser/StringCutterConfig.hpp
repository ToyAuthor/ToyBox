
#pragma once

#include "toy/Standard.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{

class TOY_API_PARSER StringCutterConfig
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

		struct TChar
		{
			TChar(char c1,char c2,char c3)
			{
				t[0]=c1;
				t[1]=c2;
				t[2]=c3;
			}
			TChar()
			{
				t[0]='b';
				t[1]='t';
				t[2]='a';
			}
			char  t[3];
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

				void clear()
				{
					array.clear();
				}

			private:

				std::vector<T>    array;
		};

		StringCutterConfig();
		~StringCutterConfig();

		void    useDefault();
		void    useDefaultIgnore();
		void    useDefaultBreak01();
		void    useDefaultBreak02();
		void    useDefaultBreak03();

		List<char>    breakCharList;
		List<CChar>   breakDoubleCharList;
		List<TChar>   breakTripleCharList;
		List<char>    ignoreCharList;
		std::string   desireWord;
};

inline std::shared_ptr<toy::parser::StringCutterConfig> NewCutterConfig()
{
	return std::make_shared<toy::parser::StringCutterConfig>();
}


}//namespace parser
}//namespace toy
