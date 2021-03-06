#include "toy/Standard.hpp"
#include "toy/math/SafeInt.hpp"

#ifdef TOY_WINDOWS
#include "toy/Windows.hpp"
#include <shellapi.h>
//#pragma comment(lib,"shell32.lib")
#endif

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

struct StatusPrivate
{
	boost::filesystem::file_status  status;
	boost::filesystem::path         name;
	std::string                     location;
	std::string                     filename;
};

bool IsFile(const std::string &filename)
{
	if ( boost::filesystem::is_regular_file(StrToPath(filename)) )
	{
		return true;
	}

	return false;
}

bool IsFolder(const std::string &filename)
{
	if ( boost::filesystem::is_directory(StrToPath(filename)) )
	{
		return true;
	}

	return false;
}

bool IsEmptyFolder(const std::string &filename)
{
	auto name = StrToPath(filename);

	if ( ! boost::filesystem::is_directory(name) )
	{
		return false;
	}

	boost::filesystem::directory_iterator    endIt;
	boost::filesystem::directory_iterator    it(name);

	if ( it == endIt )
	{
		return true;
	}

	return false;
}

bool IsExist(const std::string &filename)
{
	return boost::filesystem::exists(StrToPath(filename));
}

uintmax_t Remove(const std::string &filename)
{
	return boost::filesystem::remove_all(StrToPath(filename));
}

bool MakeDir(const std::string &filename)
{
	return boost::filesystem::create_directories(StrToPath(filename));
}

uint64_t GetFileSize(const std::string &filename)
{
	return toy::math::SafeInt<uint64_t>(boost::filesystem::file_size(StrToPath(filename)),TOY_MARK);
}

// Linux   $ xdg-open [directory]
// Mac     $ open [directory]
// Windows $ start [directory]
bool OpenFolder(const std::string &filename)
{
	#ifdef TOY_WINDOWS
	ShellExecuteW(nullptr,L"open",nullptr,nullptr,toy::utf::UTF8ToWChar(filename).c_str(),SW_SHOWNORMAL);
	#elif defined(TOY_MAC)
	toy::Execute((std::string("open ")+filename).c_str());
	#else
	// Open up by default file manager
	toy::Execute((std::string("xdg-open ")+filename).c_str());
//	toy::Execute((std::string("nautilus ")+filename).c_str());
	#endif

	return true;
}

}}

using namespace toy;
using namespace path;

Status::Status(const std::string &filename):_this(new StatusPrivate)
{
	_this->name = StrToPath(filename);
	_this->status = boost::filesystem::status(_this->name);
	_this->location = PathToStr(_this->name.parent_path());
	_this->filename = PathToStr(_this->name.filename());
}

Status::Status(const Status &other):_this(new StatusPrivate)
{
	_this->name     = other._this->name;
	_this->status   = other._this->status;
	_this->location = other._this->location;
	_this->filename = other._this->filename;
}

Status::~Status()
{
	;
}

void Status::operator = (const Status &other)
{
	_this->name     = other._this->name;
	_this->status   = other._this->status;
	_this->location = other._this->location;
	_this->filename = other._this->filename;
}

void Status::operator = (const std::string &filename)
{
	_this->name = StrToPath(filename);
	_this->status = boost::filesystem::status(_this->name);
	_this->location = PathToStr(_this->name.parent_path());
	_this->filename = PathToStr(_this->name.filename());
}

bool Status::exist()
{
	return boost::filesystem::exists(_this->status);
}

void Status::remove()
{
	boost::filesystem::remove_all(_this->name);
	_this->status = boost::filesystem::status(_this->name);
}

uint64_t Status::size()
{
	return toy::math::SafeInt<uint64_t>(boost::filesystem::file_size(_this->name),TOY_MARK);
}

std::string Status::location()
{
	return _this->location;
}

std::string Status::name()
{
	return _this->filename;
}

bool Status::isDirectory()
{
	return boost::filesystem::is_directory(_this->status);
}

bool Status::isFile()
{
	return boost::filesystem::is_regular_file(_this->status);
}
