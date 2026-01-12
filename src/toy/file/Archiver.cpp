#include "toy/Exception.hpp"
#include "toy/file/Archiver.hpp"
#include "toy/file/ArchiverBase.hpp"
#include "toy/file/archiver/ArchiverZip.hpp"
#include "toy/file/archiver/Archiver7Zip.hpp"
#include "toy/file/archiver/ArchiverDefaultZip.hpp"

using namespace toy;
using namespace file;

Archiver::Archiver(enum toy::Option format)
{
	switch ( format )
	{
		case toy::DEFAULT:
		//	_this.reset(new ArchiverDefaultZip);
		//	break;
		case toy::ZIP:
			_this.reset(new ArchiverZip);
			break;
		case toy::SEVEN_ZIP:
			_this.reset(new Archiver7Zip);
			break;
		default:
			throw toy::Exception(TOY_MARK);
	}
}

Archiver::~Archiver()
{
	;
}

bool Archiver::compress(const std::string &input, const std::string &output)
{
	return _this->compress(input,output);
}

bool Archiver::decompress(const std::string &input, const std::string &output)
{
	return _this->decompress(input,output);
}
