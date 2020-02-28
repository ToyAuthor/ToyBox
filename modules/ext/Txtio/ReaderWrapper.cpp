#include <toy/Exception.hpp>
#include <toy/Log.hpp>
#include <toy/io/Reader.hpp>
#include "ReaderWrapper.hpp"

ReaderWrapper::ReaderWrapper(lua::Str filename):_reader(new toy::io::Reader<>)
{
	if ( ! this->loadText(filename) )
	{
		toy::Logger<<"load text file failed"<<toy::NewLine;
		throw toy::Exception(TOY_MARK);
	}
}

ReaderWrapper::~ReaderWrapper()
{
	this->drop();
}

lua::Bool ReaderWrapper::loadText(lua::Str filename)
{
	if ( _reader==nullptr )return false;

	return _reader->open(filename);
}

void ReaderWrapper::open(lua::Str filename)
{
	if ( ! this->loadText(filename) )
	{
		toy::Logger<<"load text file failed"<<toy::NewLine;
		throw toy::Exception(TOY_MARK);
	}
}

lua::Var ReaderWrapper::nextLine()
{
	if ( _reader==nullptr )return lua::Nil();

	lua::Str   str;

	if ( _reader->nextLine(&str) )
	{
		return str;
	}
	else
	{
		return lua::Nil();
	}
}

void ReaderWrapper::drop()
{
	_reader = nullptr;
}
