
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

		bool    openDir(std::string path);           // Open a folder or archive.
		bool    open(std::string filepath);
		bool    read(void *file,uint32_t size);
		bool    write(void *file,uint32_t size);     // Not finish yet.
		bool    seek(enum SeekOption option,int32_t offset);// Not finish yet.

//		void    close();// Do it later.

		bool    isEmpty();

		void    changeMode(enum Mode);
//		bool    readFrom(const tchar *file);    // A path or a archive.
//		bool    readFrom(String file);

		std::string   getFileName();
		void*   getFilePointer();               // It's made for libpng. Bad design.

	private:

		void    freeIO();

		file::io::Base*     _io = nullptr;
		enum Mode           _mode = NONE;

};

}//namespace toy
