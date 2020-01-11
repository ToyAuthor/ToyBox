#include "toy/file/File.hpp"
#include "toy/file/io/Standard.hpp"
#include "toy/file/io/DefaultZip.hpp"
#include "toy/file/io/Zlib.hpp"
#include "toy/file/io/SevenZip.hpp"
#include "toy/file/io/Android.hpp"

using namespace toy;

File::File(enum toy::Option mode)
{
	changeMode(mode);
}

File::File(std::shared_ptr<toy::file::ArchiveFacade> facade)
{
	changeMode(facade);
}

File::~File()
{
	freeIO();
}

void File::freeIO()
{
	if (_io)
	{
		_mode = toy::NOTHING;
		_io = nullptr;
	}
}

void File::changeMode(std::shared_ptr<toy::file::ArchiveFacade> facade)
{
	freeIO();
	_mode = toy::SPECIAL;
	_io = facade;
}

void File::changeMode(enum toy::Option mode)
{
	if ( _mode==mode )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	freeIO();
	_mode = mode;

//	#ifndef TOY_ANDROID
//	if ( mode==ANDROID_MGR )
//	{
//		toy::Oops(TOY_MARK);
//		return;
//	}
//	#endif

	switch (mode)
	{
		case toy::DIRECTORY:
			_io = std::make_shared<file::io::Standard>();
			break;
		case toy::DEFAULT:
		//	_io = std::make_shared<file::io::DefaultZip>();
		//	break;
		case toy::ZIP:
			_io = std::make_shared<file::io::Zlib>();
			break;
		case toy::SEVEN_ZIP:
			_io = std::make_shared<file::io::SevenZip>();
			break;
//		case ANDROID_MGR:
//			_io = std::make_shared<file::io::Android>();
//			break;
		default:
			toy::Oops(TOY_MARK);
	}
}

bool File::openDir(std::string path)
{
	return _io->openDir(path);
}

void File::closeDir()
{
	_io->closeDir();
}

bool File::open(std::string filepath)
{
	return _io->open(filepath);
}

void File::close()
{
	_io->close();
}

uint32_t File::read(void *file,uint32_t size)
{
	return _io->read(file,size);
}

bool File::write(const void *file,uint32_t size)
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

bool File::isEnd()
{
	return _io->isEnd();
}

bool File::isEmpty()
{
	return _io->isEmpty();
}

std::string File::getFileName()
{
	return _io->getFileName();
}

std::string File::getDirName()
{
	return _io->getDirName();
}
