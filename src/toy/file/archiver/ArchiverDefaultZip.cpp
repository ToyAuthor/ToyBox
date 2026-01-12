#include "toy/path/Status.hpp"
#include "toy/path/Browser.hpp"
#include "toy/file/archiver/ArchiverDefaultZip.hpp"

using namespace toy;
using namespace file;

ArchiverDefaultZip::ArchiverDefaultZip()
{
	;
}

ArchiverDefaultZip::~ArchiverDefaultZip()
{
	;
}

bool ArchiverDefaultZip::compress(const std::string &input, const std::string &output)
{
	(void)input;
	(void)output;

	return true;
}

bool ArchiverDefaultZip::decompress(const std::string &input, const std::string &output)
{
	toy::path::Status   source(input);

	if ( (! source.exist()) || (!source.isFile()) )
	{
		return false;
	}

//	uint64_t   totalSize = source.size();

	toy::path::Status   target(output);

	if (  target.exist() )
	{
		return false;
	}

	toy::path::MakeDir(output);

	return true;
}
