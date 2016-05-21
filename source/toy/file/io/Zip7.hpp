
#pragma once

#include <cstdio>
#include "toy/file/io/Base.hpp"

//------Come from 7zip------start
#include "C/7z.h"
#include "C/7zCrc.h"
#include "C/7zFile.h"
#include "C/7zVersion.h"
#include "C/Alloc.h"
#include "C/Bra.h"
#include "C/LzmaDec.h"
//------Come from 7zip------end

namespace toy{
namespace file{
namespace io{


class Zip7 : public Base
{
	public:

		Zip7();
		virtual ~Zip7(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual int     read(void *file,uint32_t size);    // Not finish yet.
		virtual bool    write(void *file,uint32_t size);
		virtual bool    seek(enum Base::Option option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd(){return 1;}     // Implement it later.
		virtual bool    isEmpty();
		virtual void*   getFilePointer();    // prohibit

	private:

		CFileInStream   _archiveStream;
		CLookToRead     _lookStream;
		CSzArEx         _db;
		ISzAlloc        _allocImp;
		ISzAlloc        _allocTempImp;
		UInt16*         _temp = nullptr;
		Byte*           _outBuffer = nullptr;

		size_t          _fileSize = 0;
		void*           _filePointer = nullptr;
};


}//namespace io
}//namespace file
}//namespace toy
