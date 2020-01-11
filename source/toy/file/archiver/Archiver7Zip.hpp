
#pragma once

#include "toy/file/ArchiverBase.hpp"
#include "toy/file/io/SevenZip.hpp"

namespace toy{
namespace file{

class Archiver7Zip : public ArchiverBase
{
	public:

		Archiver7Zip();
		~Archiver7Zip();

		bool compress(const std::string &input, const std::string &output);
		bool decompress(const std::string &input, const std::string &output);

	private:

		::toy::file::io::SevenZip   _core;
};

}}
