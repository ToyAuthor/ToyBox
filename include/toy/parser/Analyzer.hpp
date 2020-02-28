
#pragma once

#include <memory>
#include "toy/Option.hpp"
#include "toy/parser/AnalyzerConfig.hpp"
#include "toy/parser/Export.hpp"

namespace toy{
namespace parser{

class _AnalyzerBuffer;

// Take string apart by given rule.
class TOY_API_PARSER Analyzer
{
	public:

		Analyzer();
		~Analyzer();

		void    loadString(const std::string &str,enum toy::Option option=toy::RIGHTWARD);
		bool    nextWord(std::string *str);    // Next token

		void    pushConfig(std::shared_ptr<AnalyzerConfig>);
		void    popConfig(int number=1);
		auto    getConfig()->std::shared_ptr<AnalyzerConfig>;
		void    pushFront(const std::string &str);
		void    drop();

	private:

		std::unique_ptr<toy::parser::_AnalyzerBuffer>  _buffer;
		std::vector<std::shared_ptr<AnalyzerConfig>>   _configStack;
		enum toy::Option                               _option = toy::NOTHING;
};



}//namespace parser
}//namespace toy
