#include "toy/Ooops.hpp"
#include "toy/file/archiver/Archiver7Zip.hpp"

using namespace toy;
using namespace file;

Archiver7Zip::Archiver7Zip()
{
	;
}

Archiver7Zip::~Archiver7Zip()
{
	;
}

bool Archiver7Zip::compress(const std::string &, const std::string &)
{
	toy::Ooops(TOY_MARK);
	return true;
}

bool Archiver7Zip::decompress(const std::string &input, const std::string &output)
{
	_core.extractFileOut(input,output);

	return true;
}
