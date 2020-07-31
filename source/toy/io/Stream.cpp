#include "toy/Environment.hpp"
#include "toy/Oops.hpp"
#include "toy/path/Status.hpp"
#include "toy/io/Stream.hpp"
#include "toy/math/SafeInt.hpp"

#ifdef TOY_WINDOWS
	#include <wchar.h>
	#include "toy/Utf.hpp"
#endif

namespace toy{
namespace io{

struct StreamPrivate
{
	FILE*      handle = nullptr;
};

}}

using namespace toy;
using namespace io;

Stream::Stream():_this(new StreamPrivate)
{
	;
}

Stream::Stream(std::string filename,enum toy::Option option):_this(new StreamPrivate)
{
	if ( ! this->open(filename,option) )
	{
		_this->handle = nullptr;
	}
}

bool Stream::empty()
{
	if ( _this->handle==nullptr )
		return true;
	else
		return false;
}

bool Stream::good()
{
	return ! this->empty();
}

Stream::~Stream()
{
	this->close();
}

bool Stream::open(std::string filename,enum toy::Option option)
{
	this->close();

	std::string str;

	switch ( option )
	{
		case toy::READ_ONLY:  str = "rb";   break;
		case toy::DEFAULT:    str = "rb+";  break;
		default:
			toy::Oops(TOY_MARK);
			return false;
	}

	toy::path::Status   status(filename);

	if ( (option!=toy::READ_ONLY) && (!status.exist()) )
	{
		auto location = status.location();

		if ( false==location.empty() )
		{
			if ( false==toy::path::IsFolder(location) )
			{
				if ( false==toy::path::MakeDir(location) )
				{
					return false;
				}
			}
		}

		#ifdef TOY_WINDOWS
			auto filePtr = ::_wfopen(toy::utf::UTF8ToWChar(filename).c_str(),L"wb");
		#else
			auto filePtr = std::fopen(filename.c_str(),"wb");
		#endif

		std::fclose(filePtr);
	}

	#ifdef TOY_WINDOWS
		#ifdef TOY_MSVC
			if ( 0 != ::_wfopen_s(&(_this->handle),toy::utf::UTF8ToWChar(filename).c_str(),toy::utf::UTF8ToWChar(str).c_str()) )
			{
				return false;
			}
		#else
			_this->handle = ::_wfopen(toy::utf::UTF8ToWChar(filename).c_str(),toy::utf::UTF8ToWChar(str).c_str());
		#endif
	#elif defined(TOY_ANDROID)
		_this->handle = fopen(filename.c_str(),str.c_str());
	#else
		_this->handle = std::fopen(filename.c_str(),str.c_str());
	#endif

	if ( _this->handle )
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint64_t Stream::read(void *ptr,uint64_t size)
{
	if ( empty() )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

    std::fseek(_this->handle, 0, SEEK_CUR);

	#if defined(TOY_ANDROID)
	uint64_t	result = fread(ptr,1,(size_t)size,_this->handle);
	#else
	uint64_t	result = std::fread(ptr,1,(size_t)size,_this->handle);
	#endif

	if ( result>size )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}

	return result;
}

bool Stream::write(const void *ptr,uint64_t size)
{
	if ( this->empty() )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	/*
	if ( option==toy::READ_ONLY)
	{
		toy::Oops(TOY_MARK);
		return false;
	}*/

	std::fseek(_this->handle, 0, SEEK_CUR);

	#if defined(TOY_ANDROID)
	fwrite(ptr,(size_t)size,1,_this->handle);
	#else
	std::fwrite(ptr,(size_t)size,1,_this->handle);
	#endif

	return true;
}

bool Stream::isEnd()
{
	if ( this->empty() )
	{
		toy::Oops(TOY_MARK);
		return true;
	}

	#if defined(TOY_ANDROID)
	if ( feof(_this->handle) )
	#else
	if ( std::feof(_this->handle) )
	#endif
	{
		return true;
	}

	return false;
}

void Stream::close()
{
	if ( _this->handle )
	{
		#if defined(TOY_ANDROID)
		fclose(_this->handle);
		#else
		std::fclose(_this->handle);
		#endif
		_this->handle = nullptr;
	}
}

bool Stream::seek(int option,int32_t offset)
{
	if ( this->empty() )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( (option==SEEK_CUR) && offset==0 ) return true;

	#if TOY_OPTION_CHECK_CAREFUL
		switch ( option )
		{
			case SEEK_SET:
			case SEEK_CUR:
			case SEEK_END:
				break;
			default:
				toy::Oops(TOY_MARK);
		}
	#endif

	#if defined(TOY_ANDROID)
//	fseek( _this->handle, offset, option );
	std::fseek(_this->handle,toy::math::SafeInt<long>(offset,TOY_MARK),option);
	#else
	std::fseek(_this->handle,toy::math::SafeInt<long>(offset,TOY_MARK),option);
//	std::fseek( _this->handle, offset, option );
	#endif

	return true;
}

void Stream::rewind()
{
	if ( _this->handle )
	{
		std::rewind(_this->handle);
	}
}

void Stream::operator >>(uint64_t offset)
{
	if ( _this->handle )
	{
		std::fseek(_this->handle,toy::math::SafeInt<long>(offset,TOY_MARK),SEEK_CUR);
	}
}

void Stream::operator <<(uint64_t offset)
{
	if ( _this->handle )
	{
		std::fseek(_this->handle,-(toy::math::SafeInt<long>(offset,TOY_MARK)),SEEK_CUR);
	}
}

void Stream::remove(const std::string &filename)
{
	toy::path::Remove(filename);
}
