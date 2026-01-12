
#pragma once

#include "toy/io/Stream.hpp"
#include "toy/file/ArchiveFacade.hpp"

namespace toy{
namespace file{
namespace io{

class Standard : public ::toy::file::ArchiveFacade
{
	public:

		Standard(){}
		virtual ~Standard(){close();}

		virtual bool    openDir(std::string path);
		virtual void    closeDir();
		virtual bool    open(std::string filepath);
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(const void *file,uint32_t size);
		virtual bool    seek(int option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd();
		virtual bool    isEmpty();
		virtual auto    getFileName()->std::string;
		virtual auto    getDirName()->std::string;

	private:

		toy::io::Stream    _file;
		std::string        _path;
		std::string        _fileName;
};

}}}
