
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"

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

class TOY_API_FILE File
{
	public:

		enum Mode:int
		{
			NONE,
			STD,
			ZIP,
			SEVEN_ZIP,
			ANDROID_MGR,
		};

		File(enum Mode mode=STD);
		~File();

		bool    openDir(std::string path);                     // Open a directory/archive for searching files.
		bool    open(std::string file);
		auto    read(void *file,uint32_t size)->uint32_t;      // Return how much data really output.
		bool    write(void *file,uint32_t size);               // STD mode supported only.
		bool    isEnd();
		bool    isEmpty();
		void    changeMode(enum Mode);
		auto    getFileName()->std::string;

		/*
		 * Not support ZIP mode.
		 *
		 * option:
		 *     SEEK_SET - Seek from the beginning of file.
		 *     SEEK_CUR - Seek from the current position of the file pointer.
		 *     SEEK_END - Seek from the end of file.
		 */
		bool    seek(int option,int32_t offset);

	private:

		void    close();
		void    freeIO();

		file::io::Base*     _io = nullptr;      // Always keep a object when it alive.
		enum Mode           _mode = NONE;       // Default mode is STD.

};

}//namespace toy
