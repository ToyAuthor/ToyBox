#include <toy/io/Writer.hpp>
#include <toy/Exception.hpp>
#include <toy/Log.hpp>
#include "WriterWrapper.hpp"

WriterWrapper::WriterWrapper(lua::Str filename):_writer(new toy::io::Writer<>)
{
	if ( ! this->newText(filename) )
	{
		toy::Logger<<"open text file failed"<<toy::NewLine;
		throw toy::Exception(TOY_MARK);
	}
}

WriterWrapper::~WriterWrapper()
{
	this->drop();
}

lua::Bool WriterWrapper::newText(lua::Str filename)
{
	if ( _writer==nullptr )return false;

	return _writer->open(filename);
}

void WriterWrapper::newLine()
{
	if ( _writer==nullptr )return;
	_writer->newLine();
}

void WriterWrapper::print(lua::Str str)
{
	if ( _writer==nullptr )return;
	_writer->print(str);
}

void WriterWrapper::printf(lua::Str str)
{
	if ( _writer==nullptr )return;
	_writer->printf(str);
}

void WriterWrapper::drop()
{
	_writer = nullptr;
}
