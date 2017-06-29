
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


class SevenZip : public Base
{
	public:

		SevenZip();
		virtual ~SevenZip(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(void *file,uint32_t size);   // Not finish yet.
		virtual bool    seek(int option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd();
		virtual bool    isEmpty();

	private:

		CFileInStream   _archiveStream;
		CLookToRead     _lookStream;
		CSzArEx         _db;
		ISzAlloc        _allocImp;
		ISzAlloc        _allocTempImp;
		UInt16*         _temp = nullptr;
		Byte*           _outBuffer = nullptr;

		//-------------------------------------------

		size_t          _fileSize = 0;
		size_t          _passSize = 0;
		void*           _fileBegin = nullptr;
};


}//namespace io
}//namespace file
}//namespace toy
