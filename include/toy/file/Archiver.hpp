/*
 ※ Only Windows OS has unicode issue.

 A:support utf-8 name of parent folder
 B:support utf-8 archive name
 C:support utf-8 file name in archive

┌--------------┬--------┬----------┬-┬-┬-┐
│              │compress│decompress│A│B│C│
├--------------┼--------┼----------┼-┼-┼-┤
│toy::ZIP      │O       │O         │X│O│O│
├--------------┼--------┼----------┼-┼-┼-┤
│toy::SEVEN_ZIP│X       │O         │O│O│O│
└--------------┴--------┴----------┴-┴-┴-┘
*/

#pragma once

#include <memory>
#include <string>
#include "toy/Option.hpp"
#include "toy/file/Export.hpp"

namespace toy{
namespace file{

class ArchiverBase;

class TOY_API_FILE Archiver
{
	public:

		/*
		 * Options:
		 *     ZIP
		 *     SEVEN_ZIP
		 */
		Archiver(enum toy::Option format);
		~Archiver();

		bool compress(const std::string &input, const std::string &output);
		bool decompress(const std::string &input, const std::string &output);

	private:

		std::unique_ptr<toy::file::ArchiverBase>   _this;
};

}}
