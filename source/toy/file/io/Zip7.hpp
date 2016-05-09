
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
		virtual ~Zip7(){Close();}

		virtual bool    OpenDir(std::string path);
		virtual bool    Open(std::string filepath);
		virtual bool    Read(void *file,uint32_t size);
		virtual bool    Write(void *file,uint32_t size);
		virtual bool    Seek(enum Base::Option option,int32_t offset);
		virtual void    Close();
		virtual bool    IsEmpty();
		virtual void*   GetFilePointer();    // prohibit

	private:

		CFileInStream   archiveStream;
		CLookToRead     lookStream;
		CSzArEx         db;
		ISzAlloc        allocImp;
		ISzAlloc        allocTempImp;
		UInt16*         temp;
		Byte*           outBuffer;

		size_t          mFileSize;
		void*           mFilePointer;
};


}//namespace io
}//namespace file
}//namespace toy
