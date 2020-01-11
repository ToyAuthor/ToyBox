#include <ctime>
#include <random>
#include "contrib/minizip/zip.h"
#include "contrib/minizip/unzip.h"
#include "toy/Environment.hpp"
#include "toy/Boost.hpp"
#include "toy/Exception.hpp"
#include "toy/Log.hpp"
#include "toy/Oops.hpp"
#include "toy/Utf.hpp"
#include "toy/io/Stream.hpp"
#include "toy/file/archiver/ArchiverZip.hpp"

using namespace toy;
using namespace file;

#ifdef TOY_WINDOWS
	static inline boost::filesystem::path StrToPath(std::string str)
	{
		return boost::filesystem::path(toy::utf::UTF8ToWChar(str));
	}

	static inline std::string PathToStr(const boost::filesystem::path &str)
	{
		return toy::utf::WCharToUTF8(str.wstring());
	}
#else
	static inline boost::filesystem::path StrToPath(std::string str)
	{
		return boost::filesystem::path(str);
	}

	static inline std::string PathToStr(const boost::filesystem::path &str)
	{
		return str.string();
	}
#endif

#ifdef TOY_WINDOWS

static char MakeRandomChar()
{
	static std::default_random_engine          engine = std::default_random_engine(std::time(nullptr));
	static std::uniform_int_distribution<int>  dis8   = std::uniform_int_distribution<int>(65,90);

	return static_cast<char>(dis8(engine));
}

class ZipOpen_Guard
{
	public:

		ZipOpen_Guard(const std::string &pathname, int append)
		{
			_fakeName = pathname;

			if ( toy::utf::IsUtf8(_fakeName) )
			{
				_originName = _fakeName;
				_fakeName = "toyzip_";

				int   count = 0;

				do
				{
					count++;
					_fakeName.push_back(MakeRandomChar());
				}
				while( boost::filesystem::exists( StrToPath(_fakeName) ) && count!=16 );

				if ( count==16 )
				{
					throw toy::Exception(TOY_MARK);
				}
			}

			_handle = zipOpen(_fakeName.c_str(), append);

			if ( _handle==nullptr )
			{
				throw toy::Exception(TOY_MARK);
			}
		}

		~ZipOpen_Guard()
		{
			zipClose(_handle, nullptr);

			try
			{
				if ( ! _originName.empty() )
				{
					if ( boost::filesystem::exists( StrToPath(_fakeName) ) )
					{
						if ( boost::filesystem::exists( StrToPath(_originName) ) )
						{
							toy::Oops(TOY_MARK);
						}
						else
						{
							boost::filesystem::rename( StrToPath(_fakeName), StrToPath(_originName) );
						}
					}
					else
					{
						toy::Oops(TOY_MARK);
					}
				}
			}
			catch (std::exception &e)
			{
				toy::Log(e);
			}
		}

		zipFile core()
		{
			return _handle;
		}

	private:

		zipFile        _handle;
		std::string    _originName;
		std::string    _fakeName;
};

class UnzOpen_Guard
{
	public:

		UnzOpen_Guard(const std::string &pathname)
		{
			_fakeName = pathname;

			if ( toy::utf::IsUtf8(_fakeName) )
			{
				_originName = _fakeName;

				_fakeName = "toyzip_";

				int   count = 0;

				do
				{
					count++;
					_fakeName.push_back(MakeRandomChar());
				}
				while( boost::filesystem::exists( StrToPath(_fakeName) ) && count!=16 );

				if ( count==16 )
				{
					throw toy::Exception(TOY_MARK);
				}

				boost::filesystem::rename( StrToPath(pathname) , StrToPath(_fakeName) );

				_handle = unzOpen(_fakeName.c_str());

				if ( _handle==nullptr )
				{
					throw toy::Exception(TOY_MARK);
				}
			}
		}

		~UnzOpen_Guard()
		{
			unzClose( _handle );

			try
			{
				if ( ! _originName.empty() )
				{
					if ( boost::filesystem::exists( StrToPath(_fakeName) ) )
					{
						if ( boost::filesystem::exists( StrToPath(_originName) ) )
						{
							toy::Oops(TOY_MARK);
						}
						else
						{
							boost::filesystem::rename( StrToPath(_fakeName), StrToPath(_originName) );
						}
					}
					else
					{
						toy::Oops(TOY_MARK);
					}
				}
			}
			catch (std::exception &e)
			{
				toy::Log(e);
			}
		}

		unzFile core()
		{
			return _handle;
		}

	private:

		unzFile        _handle;
		std::string    _originName;
		std::string    _fakeName;
};

#else

// Make sure always call zipClose after zipOpen.
class ZipOpen_Guard
{
	public:

		ZipOpen_Guard(const std::string &pathname, int append)
		{
			_handle = zipOpen(pathname.c_str(), append);

			if ( _handle==nullptr )
			{
				throw toy::Exception(TOY_MARK);
			}
		}

		~ZipOpen_Guard()
		{
			zipClose(_handle, nullptr);
		}

		zipFile core()
		{
			return _handle;
		}

	private:

		zipFile    _handle;
};

class UnzOpen_Guard
{
	public:

		UnzOpen_Guard(const std::string &pathname)
		{
			_handle = unzOpen(pathname.c_str());

			if ( _handle==nullptr )
			{
				throw toy::Exception(TOY_MARK);
			}
		}

		~UnzOpen_Guard()
		{
			unzClose( _handle );
		}

		unzFile core()
		{
			return _handle;
		}

	private:

		unzFile    _handle;
};

#endif

class UnzCurrentFile
{
	public:

		UnzCurrentFile(unzFile h):_handle(h)
		{
			if ( unzOpenCurrentFile( _handle ) != UNZ_OK )
			{
				throw toy::Exception(TOY_MARK);
			}
		}

		~UnzCurrentFile()
		{
			unzCloseCurrentFile( _handle );
		}

		void makeFile(boost::filesystem::path name, uint8_t *buffer,uint32_t BUFFER_SIZE)
		{
			boost::filesystem::create_directories(name.parent_path());

			toy::io::Stream    iodev(PathToStr(name));

			uint32_t    size;

			for (;;)
			{
				size = unzReadCurrentFile( _handle, buffer, BUFFER_SIZE );

				if ( size==0 )
				{
					break;
				}

				if ( iodev.write(buffer,size)==false )
				{
					throw toy::Exception(TOY_MARK);
				}

				if ( size<BUFFER_SIZE )
				{
					break;
				}
			}
		}

	private:

		unzFile    _handle;
};

// Make sure always call zipCloseFileInZip after zipOpenNewFileInZip.
class ZipOpenNewFileInZip_Guard
{
	public:

		ZipOpenNewFileInZip_Guard( zipFile                core,
		                           const std::string&     filename,
		                           const zip_fileinfo*    zipfi,
		                           const void*            extrafield_local,
		                           unsigned int           size_extrafield_local,
		                           const void*            extrafield_global,
		                           unsigned int           size_extrafield_global,
		                           const char*            comment,
		                           int                    method,
		                           int                    level ):_handle(core)
		{
			zipOpenNewFileInZip( _handle,
			                     filename.c_str(),
			                     zipfi,
			                     extrafield_local,
			                     size_extrafield_local,
			                     extrafield_global,
			                     size_extrafield_global,
			                     comment,
			                     method,
			                     level );
		}

		~ZipOpenNewFileInZip_Guard()
		{
			zipCloseFileInZip(_handle);
		}

	private:

		zipFile    _handle;
};

ArchiverZip::ArchiverZip()
{
	;
}

ArchiverZip::~ArchiverZip()
{
	;
}

static void AddDirToZip(zipFile handle, const std::string &fileNameInZip)
{
	zip_fileinfo   info;

	info.tmz_date.tm_sec = 0;
	info.tmz_date.tm_min = 0;
	info.tmz_date.tm_hour = 0;
	info.tmz_date.tm_mday = 0;
	info.tmz_date.tm_mon = 0;
	info.tmz_date.tm_year = 0;
	info.dosDate = 0;
	info.internal_fa = 0;
	info.external_fa = 0;

	ZipOpenNewFileInZip_Guard   dev(handle, fileNameInZip+R"(/)", &info, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION);
}

static void AddFileToZip(zipFile handle, const std::string &fileNameInZip, const boost::filesystem::path &srcFile)
{
	zip_fileinfo info;

	info.tmz_date.tm_sec = 0;
	info.tmz_date.tm_min = 0;
	info.tmz_date.tm_hour = 0;
	info.tmz_date.tm_mday = 0;
	info.tmz_date.tm_mon = 0;
	info.tmz_date.tm_year = 0;
	info.dosDate = 0;
	info.internal_fa = 0;
	info.external_fa = 0;

	ZipOpenNewFileInZip_Guard   dev(handle, fileNameInZip, &info, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

	toy::io::Stream     reader;

	if ( ! reader.open(PathToStr(srcFile), toy::READ_ONLY) )
	{
		return;
	}

	char buf[128*1024];

	uint32_t size;

	while ( ! reader.isEnd() )
	{
		size = reader.read(buf,sizeof(buf));
		zipWriteInFileInZip(handle, buf, size);
	}
}

static bool IsFolderHasChild(const boost::filesystem::path &path)
{
	if ( ! boost::filesystem::is_directory(path) )
	{
		return false;
	}

	boost::filesystem::directory_iterator    endIt;
	boost::filesystem::directory_iterator    it(path);

	if ( it == endIt )
	{
		return false;
	}

	return true;
}

static void FolderToZip( zipFile                        handle,
                         const boost::filesystem::path& sourceDir,
                         const boost::filesystem::path& parentDir )
{
	namespace boostfs = ::boost::filesystem;

	if ( IsFolderHasChild(sourceDir) )
	{
		boostfs::path   fileName;

		for ( auto it = boostfs::directory_iterator(sourceDir) ; it != boostfs::directory_iterator() ; it++ )
		{
			fileName = parentDir/it->path().filename();

			if ( boostfs::is_directory(it->path()) )
			{
				AddDirToZip(handle, PathToStr(fileName));
				FolderToZip(handle, it->path(), fileName);
			}
			else
			{
				AddFileToZip(handle, PathToStr(fileName), it->path());
			}
		}
	}
}

bool ArchiverZip::compress(const std::string &input, const std::string &output)
{
	ZipOpen_Guard    zipDevice(output, APPEND_STATUS_CREATE);

	FolderToZip(zipDevice.core(), StrToPath(input), StrToPath(""));
//	boost::filesystem::path   inputDir = StrToPath(input);
//	FolderToZip(zipDevice.core(), inputDir, inputDir.filename());

	return true;
}

static void ZipToFolder( unzFile                        handle,
                         const unz_global_info&         info,
                         const boost::filesystem::path& targetDir )
{
	const uint32_t             MAX_FILENAME = 512;
	const uint32_t             BUFFER_SIZE = 1024;
	char                       filename[ MAX_FILENAME ];
	uint8_t                    buffer[BUFFER_SIZE];
	unz_file_info              fileInfo;

	for( uLong i = info.number_entry ; i>0 ; i-- )
	{
		if( unzGetCurrentFileInfo( handle, &fileInfo, filename, MAX_FILENAME, nullptr, 0, nullptr, 0 ) != UNZ_OK )
		{
			throw toy::Exception(TOY_MARK);
		}

		UnzCurrentFile    fileDev(handle);

		fileDev.makeFile(targetDir/StrToPath(filename),buffer,BUFFER_SIZE);

		if( i!=1 && unzGoToNextFile( handle ) != UNZ_OK )
		{
			throw toy::Exception(TOY_MARK);
		}
	}
}

bool ArchiverZip::decompress(const std::string &input, const std::string &output)
{
	UnzOpen_Guard    zipDevice(input);

	unz_global_info  info;

	if( unzGetGlobalInfo( zipDevice.core(), &info ) != UNZ_OK )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	ZipToFolder(zipDevice.core(), info, StrToPath(output));

	return true;
}
