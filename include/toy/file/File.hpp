
#pragma once

#include "toy/Standard.hpp"

namespace toy
{
	namespace file
	{
		namespace io
		{
			class Base;
		}
	}
}

namespace toy{

class TOY_API File
{
	public:

		enum Mode
		{
			NONE,
			STD,        // Default mode. As same as <stdio.h>.
			ZIP,        // As *.zip as folder.
			ZIP7,       // 7zip
		};

		enum SeekOption
		{
			SET=0,      // Seek from the head of file.
			END,        // Seek from the end of file.
			CUR,        // Seek from the pointer of file.
		};

		File(enum Mode mode=STD);
		~File();

		bool    OpenDir(std::string path);           // Open a folder or archive.
		bool    Open(std::string filepath);
		bool    Read(void *file,uint32_t size);
		bool    Write(void *file,uint32_t size);
		bool    Seek(enum SeekOption option,int32_t offset);

//		void    Close();// Do it later.

		bool    IsEmpty();

		void    ChangeMode(enum Mode);
//		bool    ReadFrom(const tchar *file);    // A path or a archive.
//		bool    ReadFrom(String file);

		std::string   GetFileName();
		void*   GetFilePointer();               // It's made for libpng. Bad design.

	private:

		void    FreeIO();

		file::io::Base*     mIO;
		enum Mode           mMode;

};

}//namespace toy
