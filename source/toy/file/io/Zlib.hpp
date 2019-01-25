
#pragma once

#include "toy/file/io/Base.hpp"
#include "contrib/minizip/unzip.h"   // It's come from zlib.

namespace toy{
namespace file{
namespace io{

class Zlib : public Base
{
	public:

		Zlib(){}
		virtual ~Zlib(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(const void *file,uint32_t size);                 // Not finish yet.
		virtual bool    seek(int option,int32_t offset);                 // Not finish yet.
		virtual void    close();
		virtual bool    isEnd();                                         // Not finish yet.
		virtual bool    isEmpty();

	private:

		unzFile            _handle = nullptr;
		unz_global_info    _info = {0,0};
		bool               _isFileOpened = false;
};

}}}
