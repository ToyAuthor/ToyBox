
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

		enum Mode:int
		{
			NONE,
			STD,
			ZIP,
			SEVEN_ZIP,
		};

		enum SeekOption:int
		{
			SET=0,      // Seek from the beginning of file.
			END,        // Seek from the end of file.
			CUR,        // Seek from the current position of the file pointer.
		};

		File(enum Mode mode=STD);
		~File();

		bool    openDir(std::string path);                     // Open a file folder for search files.
		bool    open(std::string file);
		int     read(void *file,uint32_t size);
		bool    write(void *file,uint32_t size);               // STD mode supported only.
		bool    seek(enum SeekOption option,int32_t offset);   // Not support ZIP mode.
		bool    isEnd();
		bool    isEmpty();
		void    changeMode(enum Mode);
		auto    getFileName()->std::string;

	private:

		void    close();
		void    freeIO();

		file::io::Base*     _io = nullptr;      // Always keep a object when it alive.
		enum Mode           _mode = NONE;       // Default mode is STD.

};

}//namespace toy
