#include "toy/file/io/Standard.hpp"


using namespace toy;
using namespace file;
using namespace io;

bool Standard::isEnd()
{
	if ( std::feof(_file)==0 )
	{
		return false;
	}

	return true;
}

bool Standard::isEmpty()
{
	if ( _file==nullptr )
		return true;
	else
		return false;
}

void Standard::close()
{
	if ( _file )
	{
		std::fclose(_file);
		_file = nullptr;
		_path.clear();
	}
}

bool Standard::openDir(std::string path)
{
	_path = path;
	return true;
}

bool Standard::open(std::string filepath)
{
	close();

	_fileName = filepath;
	std::string   path;

	if ( _path.size()==0 )
	{
		path = _fileName;
	}
	else
	{
		path = _path + "/" + _fileName;
	}

	_file = std::fopen(path.c_str(),"rb+");

	if ( _file )
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

uint32_t Standard::read(void *file,uint32_t sizein32)
{
	#if TOY_OPTION_CHECK
		if ( file==nullptr )
		{
			toy::Oops(TOY_MARK);
			return 0;
		}
	#endif

	if ( isEmpty() )  return 0;

	#if TOY_OPTION_CHECK
		if ( sizeof(uint32_t) > sizeof(std::size_t) )
		{
			if ( sizein32 > static_cast<uint32_t>(std::numeric_limits<std::size_t>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	auto   size = static_cast<std::size_t>(sizein32);

	auto   result = std::fread(file,1,size,_file);

	if ( result>size )
	{
		// fread() has wrong
		toy::Log("ask size:%d,result size:%d\n",size,result);
		toy::Oops(TOY_MARK);
		return 0;
	}

	return result;
}

bool Standard::write(const void *file,uint32_t sizein32)
{
	if ( isEmpty() ) return false;

	#if TOY_OPTION_CHECK
		if ( sizeof(uint32_t) > sizeof(std::size_t) )
		{
			if ( sizein32 > static_cast<uint32_t>(std::numeric_limits<std::size_t>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	auto   size = static_cast<std::size_t>(sizein32);

	std::fwrite(file,size,1,_file);

	return true;
}

bool Standard::seek(int option,int32_t offset32)
{
	if ( isEmpty() ) return false;

	#if TOY_OPTION_CHECK
		if ( sizeof(int32_t) > sizeof(long) )
		{
			if ( offset32 > static_cast<int32_t>(std::numeric_limits<long>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	long offset = static_cast<long>(offset32);

	std::fseek( _file, offset, option );

	return true;
}
