#include "toy/file/File.hpp"
#include "toy/file/io/Base.hpp"
#include "toy/file/io/Standard.hpp"
#include "toy/file/io/Zlib.hpp"
#include "toy/file/io/SevenZip.hpp"


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
		Oops(TOY_MARK);
		return;
	}

	freeIO();
	_mode = mode;

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
		case NONE:
		default:
			// NONE is not a option.
			Oops(TOY_MARK);
	}
}

bool File::changeDirectory(std::string path)
{
	return _io->openDir(path);
}

bool File::open(std::string filepath)
{
	return _io->open(filepath);
}

int File::read(void *file,uint32_t size)
{
	return _io->read(file,size);
}

bool File::write(void *file,uint32_t size)
{
	return _io->write(file,size);
}

bool File::seek(enum SeekOption option,int32_t offset)
{
	return _io->seek((enum file::io::Base::Option)option,offset);
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
