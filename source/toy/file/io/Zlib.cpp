#include "toy/math/SafeInt.hpp"
#include "toy/file/io/Zlib.hpp"

using namespace toy;
using namespace file;
using namespace io;

Zlib::~Zlib()
{
	closeDir();
}

bool Zlib::openDir(std::string path)
{
	closeDir();

	_handle = unzOpen(path.c_str());

	if( _handle == nullptr )
	{
		Oops(TOY_MARK);
		return false;
	}

	if( unzGetGlobalInfo( _handle, &_info ) != UNZ_OK )
	{
		toy::Oops(TOY_MARK);
		close();
		return false;
	}

	return true;
}

void Zlib::closeDir()
{
	if ( _handle )
	{
		close();

		unzClose( _handle );
		_handle = nullptr;
	}
}

bool Zlib::open(std::string filepath)
{
	close();

	const uint32_t  MAX_FILENAME = 512;
	char            filename[ MAX_FILENAME ];
	std::string     name;
	unz_file_info   fileInfo;

	for( uLong i = _info.number_entry ; i>0 ; i-- )
	{
		if( unzGetCurrentFileInfo( _handle, &fileInfo, filename, MAX_FILENAME, nullptr, 0, nullptr, 0 ) != UNZ_OK )
		{
			toy::Oops(TOY_MARK);
			close();
			return false;
		}

		name = filename;

		if( name==filepath )
		{
			if ( unzOpenCurrentFile( _handle ) != UNZ_OK )
			{
				toy::Oops(TOY_MARK);
				close();
				return false;
			}

			_isFileOpened = true;

			return true;
		}
		else
		{
			if( i!=1 && unzGoToNextFile( _handle ) != UNZ_OK )
			{
				toy::Oops(TOY_MARK);
				close();
				return false;
			}
		}
	}

	// Can't find out file.
	return false;
}

uint32_t Zlib::read(void *file, uint32_t size)
{
	int   result = unzReadCurrentFile( _handle, file, toy::math::SafeInt<unsigned>(size,TOY_MARK) );

	if ( result < 0 )
	{
		toy::Oops(TOY_MARK);
		close();
		return 0;
	}

	return result;
}

bool Zlib::write(const void *,uint32_t )
{
	// No support.
	Oops(TOY_MARK);
	return false;
}

bool Zlib::seek(int ,int32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return false;
}

void Zlib::close()
{
	if ( _handle )
	{
		if ( _isFileOpened )
		{
			unzCloseCurrentFile( _handle );
			_isFileOpened = false;
		}
	}
}

bool Zlib::isEnd()
{
	// Not ready yet
	Oops(TOY_MARK);
	return false;
}

bool Zlib::isEmpty()
{
	return ! _isFileOpened;
}

std::string Zlib::getFileName()
{
	return std::string();
}

std::string Zlib::getDirName()
{
	return std::string();
}
