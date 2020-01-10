
#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include "toy/CompilerConfig.hpp"
#include "toy/Option.hpp"

namespace toy{
namespace io{

struct StreamPrivate;

// A simple file stream. Unicode file name supported.
class TOY_API Stream
{
	public:

		Stream();
		Stream(std::string filename,enum toy::Option option=toy::DEFAULT);
		//Stream(std::string filename,std::string option);
		~Stream();

		bool empty();
		bool good();
		/*
		 * Option:
		 *     DEFAULT   :open a file for input and output
		 *     READ_ONLY :return false if target doesn't exist
		 */
		bool open(std::string filename,enum toy::Option option=toy::DEFAULT);
	//	bool open(std::string filename,std::string option);
		auto read(void *ptr,uint64_t size)->uint64_t;
		bool write(const void *ptr,uint64_t size);
		bool isEnd();
		void close();
		bool seek(int option,int32_t offset);
		void rewind();
		void operator >>(uint64_t offset);    // Just fseek(,offset,SEEK_CUR);
		void operator <<(uint64_t offset);
		void remove(const std::string &filename);   // Force remove target file.

	private:

		std::unique_ptr<StreamPrivate>    _this;
};

}}
