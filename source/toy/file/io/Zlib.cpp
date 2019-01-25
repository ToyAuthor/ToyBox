#include "toy/file/io/Zlib.hpp"

using namespace toy;
using namespace file;
using namespace io;

bool Zlib::openDir(std::string path)
{
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

bool Zlib::open(std::string filepath)
{
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
	#if TOY_OPTION_CHECK
		if ( sizeof(uint32_t) > sizeof(unsigned) )
		{
			if ( size > static_cast<uint32_t>(std::numeric_limits<unsigned>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	int   result = unzReadCurrentFile( _handle, file, static_cast<unsigned>(size) );

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
	// Not ready yet
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

		unzClose( _handle );
		_handle = nullptr;
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
