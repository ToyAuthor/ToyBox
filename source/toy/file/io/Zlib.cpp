#include "toy/file/io/Zlib.hpp"

using namespace toy;
using namespace file;
using namespace io;



Zlib::Zlib():mHandle(NULL),fFileOpened(0)
{}

bool Zlib::OpenDir(std::string path)
{
	mHandle = unzOpen(path.c_str());

	if( mHandle == NULL )
	{
		Oops(TOY_MARK);
		return 0;
	}

	if( unzGetGlobalInfo( mHandle, &mInfo ) != UNZ_OK )
	{
		Oops(TOY_MARK);
		Close();
		return 0;
	}

	return 1;
}

bool Zlib::Open(std::string filepath)
{
	const uint32_t  MAX_FILENAME = 512;
	char            filename[ MAX_FILENAME ];
	std::string     looking_for = filepath;
	std::string     name;
	unz_file_info   file_info;

	for( uLong i = mInfo.number_entry ; i>0 ; i-- )
	{
		if( unzGetCurrentFileInfo( mHandle, &file_info, filename, MAX_FILENAME, NULL, 0, NULL, 0 ) != UNZ_OK )
		{
			Oops(TOY_MARK);
			Close();
			return 0;
		}

		name = filename;

		if( name==looking_for )
		{
			if ( unzOpenCurrentFile( mHandle ) != UNZ_OK )
			{
				Oops(TOY_MARK);
				Close();
				return 0;
			}

			fFileOpened=1;

			return 1;
		}
		else
		{
			if( i!=1 && unzGoToNextFile( mHandle ) != UNZ_OK )
			{
				Oops(TOY_MARK);
				Close();
				return 0;
			}
		}
	}

	// Can't find out file.
	return 0;
}

bool Zlib::Read(void *file, uint32_t size)
{
	int error = UNZ_OK;

	error = unzReadCurrentFile( mHandle, file, size );

	if ( error < 0 )
	{
		Oops(TOY_MARK);
		Close();
		return 0;
	}

	return 1;
}

bool Zlib::Write(void *,uint32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return 1;
}

bool Zlib::Seek(enum Base::Option ,int32_t )
{
	// Not ready yet
	Oops(TOY_MARK);
	return 1;
}

void Zlib::Close()
{
	if(mHandle)
	{
		if(fFileOpened)
		{
			unzCloseCurrentFile( mHandle );
			fFileOpened=0;
		}

		unzClose( mHandle );
		mHandle = nullptr;
	}
}

bool Zlib::IsEmpty()
{
	return 1;
}

void* Zlib::GetFilePointer()
{
	// There is no way to do it.
	Oops(TOY_MARK);
	return nullptr;
}
