/*
 A:support utf-8 name of parent folder
 B:support utf-8 folder/archive name
 C:support utf-8 file name in folder/archive

┌----------┬----┬-----┬-┬-┬-┐
│          │read│write│A│B│C│
├----------┼----┼-----┼-┼-┼-┤
│std::fopen│O   │O    │O│O│O│
├----------┼----┼-----┼-┼-┼-┤
│zip       │O   │X    │X│O│O│
├----------┼----┼-----┼-┼-┼-┤
│7zip      │O   │X    │O│O│O│
└----------┴----┴-----┴-┴-┴-┘

 ※ Only Windows OS has unicode issue.
*/

#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"
#include "toy/file/ArchiveFacade.hpp"

namespace toy{

class TOY_API_FILE File
{
	public:

		/*
		 * Options:
		 *     DIRECTORY
		 *     ZIP
		 *     SEVEN_ZIP
		 */
		File(enum toy::Option mode=toy::DIRECTORY);
		File(std::shared_ptr<toy::file::ArchiveFacade>);
		~File();

		bool    openDir(std::string path);                     // Open a directory/archive for searching files and close previous directory/archive if exist.
		void    closeDir();                                    // Close the directory/archive and file stream if exist.
		bool    open(std::string filename);                    // Open a file stream and close previous stream if exist.
		void    close();                                       // Close the file stream if exist.
		auto    read(void *buffer,uint32_t size)->uint32_t;    // Return how much data have read.
		bool    write(const void *buffer,uint32_t size);
		bool    isEnd();
		bool    isEmpty();                                     // Return false if no file stream exist.
		auto    getFileName()->std::string;
		auto    getDirName()->std::string;                     // Return a directory path or archive name. Return empty string if target doesn't exist.

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

		void    freeIO();

		std::shared_ptr<::toy::file::ArchiveFacade>  _io   = nullptr;         // Always keep a object when it alive.
		enum toy::Option                             _mode = toy::NOTHING;

		#if TOY_OPTION_ENABLE_ALPHA_API
	public:
		#endif

		void    changeMode(enum toy::Option);
		void    changeMode(std::shared_ptr<toy::file::ArchiveFacade>);
};

}//namespace toy
