#include "toy/math/SafeInt.hpp"
#include "toy/file/io/Standard.hpp"

namespace temp = ::toy::file::io;

bool temp::Standard::isEnd()
{
	return _file.isEnd();
}

bool temp::Standard::isEmpty()
{
	return _file.empty();
}

void temp::Standard::close()
{
	if ( _file.good() )
	{
		_file.close();
	}
}

void temp::Standard::closeDir()
{
	close();

	_path.clear();
}

bool temp::Standard::openDir(std::string path)
{
	closeDir();

	_path = path;

	return true;
}

bool temp::Standard::open(std::string filepath)
{
	close();

	_fileName = filepath;
	std::string   path;

	if ( _path.size()==0 )
	{
		return false;
	}
	else if ( _path=="." )
	{
		path = _fileName;
	}
	else
	{
		path = _path + "/" + _fileName;
	}

	_file.open(path);

	if ( _file.good() )
	{
		return true;
	}
	else
	{
		toy::Logger<<path<<" not found"<<toy::NewLine;
		toy::Oops(TOY_MARK);
		return false;
	}
}

uint32_t temp::Standard::read(void *file,uint32_t sizein32)
{
	if ( _file.empty() )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

	auto   size = toy::math::SafeInt<std::size_t>(sizein32,TOY_MARK);

	auto   result = _file.read(file,size);

	if ( result>size )
	{
		// fread() has wrong
		toy::Log("ask size:%d,result size:%d\n",size,result);
		toy::Oops(TOY_MARK);
		return 0;
	}

	return result;
}

bool temp::Standard::write(const void *file,uint32_t sizein32)
{
	if ( isEmpty() ) return false;

	auto   size = toy::math::SafeInt<std::size_t>(sizein32,TOY_MARK);

	_file.write(file,size);

	return true;
}

bool temp::Standard::seek(int option,int32_t offset32)
{
	if ( isEmpty() ) return false;

	long offset = toy::math::SafeInt<long>(offset32,TOY_MARK);

	return _file.seek(option, offset);
}

std::string temp::Standard::getFileName()
{
	return _fileName;
}

std::string temp::Standard::getDirName()
{
	return _path;
}
