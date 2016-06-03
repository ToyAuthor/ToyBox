
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
			STD,        // Default mode. toy::File is similar to std::fstream in this mode.
			ZIP,
			SEVEN_ZIP,
		};

		enum SeekOption
		{
			SET=0,      // Seek from the beginning of file.
			END,        // Seek from the end of file.
			CUR,        // Seek from the current position of the file pointer.
		};

		File(enum Mode mode=STD);
		~File();

		bool    changeDirectory(std::string path);             // Open a file folder or zip archive for search files.
		bool    open(std::string filepath);

		int     read(void *file,uint32_t size);
		bool    write(void *file,uint32_t size);               // STD mode supported only.
		bool    seek(enum SeekOption option,int32_t offset);   // Not support ZIP mode.
		bool    isEnd();

		bool    isEmpty();
		void    changeMode(enum Mode);

		std::string   getFileName();

	private:

		void    close();
		void    freeIO();

		file::io::Base*     _io = nullptr;      // Always keep a object when it alive.
		enum Mode           _mode = NONE;

};

}//namespace toy
