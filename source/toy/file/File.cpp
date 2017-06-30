#include "toy/file/File.hpp"
#include "toy/file/io/Base.hpp"
#include "toy/file/io/Standard.hpp"
#include "toy/file/io/Zlib.hpp"
#include "toy/file/io/SevenZip.hpp"
#include "toy/file/io/Android.hpp"


using namespace toy;

File::File(enum Mode mode)
{
	changeMode(mode);
}

File::~File()
{
	freeIO();
}

void File::freeIO()
{
	if (_io)
	{
		delete _io;
		_mode = File::NONE;
		_io = nullptr;
	}
}

void File::close()
{
	_io->close();
}

void File::changeMode(enum Mode mode)
{
	if ( _mode==mode )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	freeIO();
	_mode = mode;

	#ifndef TOY_ANDROID
	if ( mode==ANDROID_MGR )
	{
		toy::Oops(TOY_MARK);
		return;
	}
	#endif

	switch (mode)
	{
		case STD:
			_io = static_cast<file::io::Base*>(new file::io::Standard);
			break;
		case SEVEN_ZIP:
			_io = static_cast<file::io::Base*>(new file::io::SevenZip);
			break;
		case ZIP:
			_io = static_cast<file::io::Base*>(new file::io::Zlib);
			break;
		case ANDROID_MGR:
			_io = static_cast<file::io::Base*>(new file::io::Android);
			break;
		case NONE:
		default:
			// NONE is not a option.
			toy::Oops(TOY_MARK);
	}
}

bool File::openDir(std::string path)
{
	return _io->openDir(path);
}

bool File::open(std::string filepath)
{
	return _io->open(filepath);
}

uint32_t File::read(void *file,uint32_t size)
{
	return _io->read(file,size);
}

bool File::write(void *file,uint32_t size)
{
	return _io->write(file,size);
}

bool File::seek(int option,int32_t offset)
{
	#if TOY_OPTION_CHECK
		switch (option)
		{
			case SEEK_SET:
			case SEEK_END:
			case SEEK_CUR:
				break;
			default:
				toy::Oops(TOY_MARK);
		}
	#endif

	return _io->seek(option,offset);
}

std::string File::getFileName()
{
	return _io->getFileName();
}

bool File::isEnd()
{
	return _io->isEnd();
}

bool File::isEmpty()
{
	return _io->isEmpty();
}
