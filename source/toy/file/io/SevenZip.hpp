
#pragma once

#include "toy/file/ArchiveFacade.hpp"

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

class SevenZip : public ::toy::file::ArchiveFacade
{
	public:

		SevenZip();
		virtual ~SevenZip();

		virtual bool    openDir(std::string path);
		virtual void    closeDir();
		virtual bool    open(std::string filepath);
		virtual void    close();
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(const void *file,uint32_t size);   // Not finish yet.
		virtual bool    seek(int option,int32_t offset);
		virtual bool    isEnd();
		virtual bool    isEmpty();
		virtual auto    getFileName()->std::string;
		virtual auto    getDirName()->std::string;

		void extractFileOut(const std::string &input,const std::string &output);

	private:

		bool            _isArchiveOpen = false;
		bool            _isFileOpen = false;
		CFileInStream   _archiveStream;
		CLookToRead     _lookStream;
		CSzArEx         _db;
		ISzAlloc        _allocImp;
		ISzAlloc        _allocTempImp;
		UInt16*         _temp = nullptr;
		Byte*           _outBuffer = nullptr;

		//-------------------------------------------

		std::size_t     _fileSize = 0;
		std::size_t     _passSize = 0;
		void*           _fileBegin = nullptr;
};

}}}
