#include "toy/file/io/Zlib.hpp"

using namespace toy;
using namespace file;
using namespace io;


bool Zlib::openDir(std::string path)
{
	_handle = unzOpen(path.c_str());

	if( _handle == NULL )
	{
		Oops(TOY_MARK);
		return 0;
	}

	if( unzGetGlobalInfo( _handle, &_info ) != UNZ_OK )
	{
		toy::Oops(TOY_MARK);
		close();
		return 0;
	}

	return 1;
}

bool Zlib::open(std::string filepath)
{
	const uint32_t  MAX_FILENAME = 512;
	char            filename[ MAX_FILENAME ];
	std::string     looking_for = filepath;
	std::string     name;
	unz_file_info   file_info;

	for( uLong i = _info.number_entry ; i>0 ; i-- )
	{
		if( unzGetCurrentFileInfo( _handle, &file_info, filename, MAX_FILENAME, NULL, 0, NULL, 0 ) != UNZ_OK )
		{
			toy::Oops(TOY_MARK);
			close();
			return 0;
		}

		name = filename;

		if( name==looking_for )
		{
			if ( unzOpenCurrentFile( _handle ) != UNZ_OK )
			{
				toy::Oops(TOY_MARK);
				close();
				return 0;
			}

			_isFileOpened=1;

			return 1;
		}
		else
		{
			if( i!=1 && unzGoToNextFile( _handle ) != UNZ_OK )
			{
				toy::Oops(TOY_MARK);
				close();
				return 0;
			}
		}
	}

	// Can't find out file.
	return 0;
}

uint32_t Zlib::read(void *file, uint32_t size)
{
	int   result = unzReadCurrentFile( _handle, file, size );

	if ( result < 0 )
	{
		toy::Oops(TOY_MARK);
		close();
		return 0;
	}

	return result;
}

bool Zlib::write(void *,uint32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return 1;
}

bool Zlib::seek(int ,int32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return 1;
}

void Zlib::close()
{
	if ( _handle )
	{
		if(_isFileOpened)
		{
			unzCloseCurrentFile( _handle );
			_isFileOpened=0;
		}

		unzClose( _handle );
		_handle = nullptr;
	}
}

bool Zlib::isEmpty()
{
	return 1;
}
