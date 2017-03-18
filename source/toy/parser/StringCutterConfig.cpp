#include "toy/parser/StringCutterConfig.hpp"


using namespace toy;
using namespace parser;

StringCutterConfig::StringCutterConfig()
{
	;
}

StringCutterConfig::~StringCutterConfig()
{
	;
}

void StringCutterConfig::useDefaultIgnore()
{
	ignoreCharList.push(' ');
	ignoreCharList.push('\t');
}

void StringCutterConfig::useDefaultBreak01()
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

void StringCutterConfig::useDefaultBreak02()
{
//	breakDoubleCharList.push(CChar('\r','\n'));
	breakDoubleCharList.push(CChar('=','='));    // ==
	breakDoubleCharList.push(CChar('!','='));    // !=
	breakDoubleCharList.push(CChar('>','='));    // >=
	breakDoubleCharList.push(CChar('<','='));    // <=
}

void StringCutterConfig::useDefaultBreak03()
{
	breakTripleCharList.push(TChar('>','>','>'));    // >>>
	breakTripleCharList.push(TChar('<','<','<'));    // <<<
	breakTripleCharList.push(TChar('"','"','"'));    // """
}

void StringCutterConfig::useDefault()
{
	useDefaultIgnore();
	useDefaultBreak01();
	useDefaultBreak02();
	useDefaultBreak03();
}
