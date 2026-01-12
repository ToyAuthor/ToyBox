
#pragma once

#include "toy/file/ArchiveFacade.hpp"
#include "contrib/minizip/unzip.h"   // It's come from zlib.

namespace toy{
namespace file{
namespace io{

class Zlib : public ::toy::file::ArchiveFacade
{
	public:

		Zlib(){}
		virtual ~Zlib();

		virtual bool    openDir(std::string path);
		virtual void    closeDir();
		virtual bool    open(std::string filepath);
		virtual void    close();
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(const void *file,uint32_t size);           // Never works.
		virtual bool    seek(int option,int32_t offset);                 // Not finish yet.
		virtual bool    isEnd();                                         // Not finish yet.
		virtual bool    isEmpty();
		virtual auto    getFileName()->std::string;
		virtual auto    getDirName()->std::string;

	private:

		unzFile            _handle = nullptr;
		unz_global_info    _info = {0,0};
		bool               _isFileOpened = false;
};

}}}
