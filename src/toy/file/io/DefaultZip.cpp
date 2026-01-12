#include "toy/file/io/DefaultZip.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

using namespace toy;
using namespace file;
using namespace io;

bool DefaultZip::isEnd()
{
	return false;
}

bool DefaultZip::isEmpty()
{
	return true;
}

void DefaultZip::close()
{
	;
}

bool DefaultZip::openDir(std::string )
{
	return true;
}

void DefaultZip::closeDir()
{
	// TBD
}

bool DefaultZip::open(std::string )
{
	return true;
}

uint32_t DefaultZip::read(void *,uint32_t )
{
	return true;
}

bool DefaultZip::write(const void *,uint32_t )
{
	if ( isEmpty() ) return 0;
	return true;
}

bool DefaultZip::seek(int ,int32_t )
{
	if ( isEmpty() ) return 0;

	return true;
}

std::string DefaultZip::getFileName()
{
	return std::string();
}

std::string DefaultZip::getDirName()
{
	return std::string();
}
