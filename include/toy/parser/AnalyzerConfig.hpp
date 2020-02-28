
#pragma once

#include "toy/Standard.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{

class TOY_API_PARSER AnalyzerConfig
{
	public:

		struct DChar
		{
			DChar(char c1,char c2)
			{
				t[0]=c1;
				t[1]=c2;
			}
			DChar()
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

				std::vector<T>& _getRef()
				{
					return array;
				}

			private:

				std::vector<T>    array;
		};

		AnalyzerConfig();
		~AnalyzerConfig();

		void    useDefault();
		void    useDefaultIgnore();
		void    useDefaultBreak01();
		void    useDefaultBreak02();
		void    useDefaultBreak03();

		std::string   desireWord;
		List<char>    ignoreCharList;
		List<TChar>   breakTripleCharList;
		List<DChar>   breakDoubleCharList;
		List<char>    breakCharList;
};

inline std::shared_ptr<toy::parser::AnalyzerConfig> NewAnalyzerConfig()
{
	return std::make_shared<toy::parser::AnalyzerConfig>();
}


}//namespace parser
}//namespace toy
