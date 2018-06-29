#include "toy/parser/AnalyzerConfig.hpp"


using namespace toy;
using namespace parser;

AnalyzerConfig::AnalyzerConfig()
{
	;
}

AnalyzerConfig::~AnalyzerConfig()
{
	;
}

void AnalyzerConfig::useDefaultIgnore()
{
	ignoreCharList.push(' ');
	ignoreCharList.push('\t');
}

void AnalyzerConfig::useDefaultBreak01()
{
	// ansi key code
	breakCharList.push('\n');
	breakCharList.push('\r');
	breakCharList.push('~');
	breakCharList.push('!');
	breakCharList.push('@');
	breakCharList.push('#');
	breakCharList.push('$');
	breakCharList.push('%');
	breakCharList.push('^');
	breakCharList.push('&');
	breakCharList.push('*');
	breakCharList.push('(');
	breakCharList.push(')');
	breakCharList.push('-');
	breakCharList.push('+');
	breakCharList.push('=');
	breakCharList.push('{');
	breakCharList.push('}');
	breakCharList.push('[');
	breakCharList.push(']');
	breakCharList.push('<');
	breakCharList.push('>');
	breakCharList.push('|');
	breakCharList.push('\\');
	breakCharList.push('/');
	breakCharList.push(':');
	breakCharList.push(';');
	breakCharList.push('"');
	breakCharList.push('\'');
	breakCharList.push(',');
	breakCharList.push('.');
	breakCharList.push('?');
}

void AnalyzerConfig::useDefaultBreak02()
{
//	breakDoubleCharList.push(CChar('\r','\n'));
	breakDoubleCharList.push(CChar('=','='));    // ==
	breakDoubleCharList.push(CChar('!','='));    // !=
	breakDoubleCharList.push(CChar('>','='));    // >=
	breakDoubleCharList.push(CChar('<','='));    // <=
}

void AnalyzerConfig::useDefaultBreak03()
{
	breakTripleCharList.push(TChar('>','>','>'));    // >>>
	breakTripleCharList.push(TChar('<','<','<'));    // <<<
	breakTripleCharList.push(TChar('"','"','"'));    // """
}

void AnalyzerConfig::useDefault()
{
	useDefaultIgnore();
	useDefaultBreak01();
	useDefaultBreak02();
	useDefaultBreak03();
}
