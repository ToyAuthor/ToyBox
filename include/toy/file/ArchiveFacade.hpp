
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace file{

class ArchiveFacade
{
	public:

		ArchiveFacade(){}
		virtual ~ArchiveFacade(){}

		virtual bool openDir(std::string path)=0;
		virtual void closeDir()=0;
		virtual bool open(std::string filepath)=0;
		virtual void close()=0;
		virtual auto read(void *file,uint32_t size)->uint32_t=0;
		virtual bool write(const void *file,uint32_t size)=0;
		virtual bool isEnd()=0;
		virtual bool isEmpty()=0;
		virtual auto getFileName()->std::string=0;
		virtual auto getDirName()->std::string=0;
		virtual bool seek(int option,int32_t offset)=0;
};

}}
