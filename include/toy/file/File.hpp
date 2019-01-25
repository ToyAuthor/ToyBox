
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

		/*
		 * Options:
		 *     DEFAULT
		 *     DIRECTORY
		 *     ZIP
		 *     SEVEN_ZIP
		 */
		File(enum toy::Option mode=toy::DIRECTORY);
		~File();

		bool    openDir(std::string path);                     // Open a directory/archive for searching files.
		bool    open(std::string file);
		auto    read(void *file,uint32_t size)->uint32_t;      // Return how much data really output.
		bool    write(const void *file,uint32_t size);         // DIRECTORY mode supported only.
		bool    isEnd();
		bool    isEmpty();
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

		file::io::Base*     _io   = nullptr;         // Always keep a object when it alive.
		enum toy::Option    _mode = toy::NOTHING;    // Default mode is STD.

		#if TOY_OPTION_ENABLE_BETA_API
	public:
		#endif

		void    changeMode(enum toy::Option);
};

}//namespace toy
