#include "toy/Boost.hpp"
#include "toy/Utf.hpp"
#include "toy/math/SafeInt.hpp"
#include "toy/path/Status.hpp"
#include "toy/path/Browser.hpp"

namespace toy{
namespace path{

#ifdef TOY_WINDOWS
	static inline auto StrToPath(const std::string &str)->boost::filesystem::path
	{
		return toy::utf::UTF8ToWChar(str);
	}

	static inline std::string PathToStr(const boost::filesystem::path &str)
	{
		return toy::utf::WCharToUTF8(str.wstring());
	}
#else
	static inline auto StrToPath(const std::string &str)->boost::filesystem::path
	{
		return boost::filesystem::path(str);
	}

	static inline std::string PathToStr(const boost::filesystem::path &str)
	{
		return str.string();
	}
#endif

struct _BrowserIteratorPrivate
{
	boost::filesystem::directory_iterator   iteratorEnd;// = boost::filesystem::directory_iterator();
	boost::filesystem::directory_iterator   iterator;
	std::string                             name;
};

struct BrowserPrivate
{
	std::string        location;
};

}}

using namespace toy;
using namespace path;

_BrowserIterator::_BrowserIterator(const std::string &pathname):_this(new _BrowserIteratorPrivate)
{
	_this->iterator = boost::filesystem::directory_iterator(StrToPath(pathname));
}

_BrowserIterator::~_BrowserIterator()
{
	;
}

_BrowserIterator::_BrowserIterator(const _BrowserIterator &mykind):_this(new _BrowserIteratorPrivate)
{
	*_this = *(mykind._this);
}

void _BrowserIterator::operator = (const _BrowserIterator &mykind)
{
	*_this = *(mykind._this);
}

bool _BrowserIterator::next()
{
	if ( _this->iterator == _this->iteratorEnd )
	{
		_this->name.clear();
		return false;
	}
	else
	{
		_this->name = PathToStr(_this->iterator->path().filename());
	}

	_this->iterator++;

	return true;
}

bool _BrowserIterator::next(std::string *str)
{
	_this->iterator++;

	if ( _this->iterator == _this->iteratorEnd )
	{
		_this->name.clear();
		return false;
	}
	else
	{
		_this->name = *str = PathToStr(_this->iterator->path().filename());
	}

	return true;
}

const std::string & _BrowserIterator::get() const
{
	return _this->name;
}

//------------------------------------------------------------------------------

Browser::Browser():_this(new BrowserPrivate)
{
	#ifdef TOY_WINDOWS
		_this->location = "d:/";
	#else
		_this->location = "/";
	#endif
}

Browser::Browser(const std::string &pathname):_this(new BrowserPrivate)
{
	_this->location = pathname;
}

Browser::~Browser()
{
	;
}

auto Browser::begin()->_BrowserIterator
{
	return _BrowserIterator(_this->location);
}
