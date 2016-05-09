
#pragma once


#include <cstdio>
#include "toy/file/io/Base.hpp"
#include "contrib/minizip/unzip.h"   // It's come from zlib.

namespace toy{
namespace file{
namespace io{


class Zlib : public Base
{
	public:

		Zlib();
		virtual ~Zlib(){Close();}

		virtual bool    OpenDir(std::string path);
		virtual bool    Open(std::string filepath);
		virtual bool    Read(void *file,uint32_t size);
		virtual bool    Write(void *file,uint32_t size);
		virtual bool    Seek(enum Base::Option option,int32_t offset);
		virtual void    Close();
		virtual bool    IsEmpty();
		virtual void*   GetFilePointer();    // prohibit

	private:

		unzFile            mHandle;
		unz_global_info    mInfo;
		int                fFileOpened;

};


}//namespace io
}//namespace file
}//namespace toy
