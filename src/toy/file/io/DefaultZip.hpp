
#pragma once

#include "toy/file/ArchiveFacade.hpp"

namespace toy{
namespace file{
namespace io{

class DefaultZip : public ::toy::file::ArchiveFacade
{
	public:

		DefaultZip(){}
		virtual ~DefaultZip(){close();}

		virtual bool openDir(std::string path);
		virtual void closeDir();
		virtual bool open(std::string filepath);
		virtual void close();
		virtual auto read(void *file,uint32_t size)->uint32_t;
		virtual bool write(const void *file,uint32_t size);
		virtual bool seek(int option,int32_t offset);
		virtual bool isEnd();
		virtual bool isEmpty();
		virtual auto getFileName()->std::string;
		virtual auto getDirName()->std::string;

	private:

};

}}}
