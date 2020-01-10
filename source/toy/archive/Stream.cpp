#include "toy/Oops.hpp"
#include "toy/archive/Stream.hpp"

namespace toy{
namespace archive{

struct StreamPrivate
{
	bool                                   isExist = false;
	toy::archive::Config                   config;
};

}}

using namespace toy;
using namespace archive;

Stream::Stream():_this(new struct ::toy::archive::StreamPrivate)
{
	;
}

Stream::Stream(const std::string &name):_this(new struct ::toy::archive::StreamPrivate)
{
	(void)name;
	;
}

Stream::~Stream()
{
	close();
}

bool Stream::open(const std::string &name)
{
	(void)name;
	return false;
}

void Stream::close()
{
	;
}

const ::toy::archive::Config& Stream::config() const
{
	return _this->config;
}
