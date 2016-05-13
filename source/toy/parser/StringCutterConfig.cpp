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

void StringCutterConfig::useDefault()
{
	ignoreCharList.push(' ');
	ignoreCharList.push('\t');
	ignoreCharList.push('\n');
	ignoreCharList.push('\r');

	// ansi key code
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

	breakDoubleCharList.push(CChar('-','>'));    // ->
	breakDoubleCharList.push(CChar(':',':'));    // ::
	breakDoubleCharList.push(CChar('<','<'));    // <<
	breakDoubleCharList.push(CChar('>','>'));    // >>
	breakDoubleCharList.push(CChar('/','/'));    // //
	breakDoubleCharList.push(CChar('/','*'));    // /*
	breakDoubleCharList.push(CChar('*','/'));    // */
	breakDoubleCharList.push(CChar('&','&'));    // &&
	breakDoubleCharList.push(CChar('|','|'));    // ||
	breakDoubleCharList.push(CChar('=','='));    // ==
	breakDoubleCharList.push(CChar('!','='));    // !=
}
