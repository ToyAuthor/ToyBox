
#pragma once

#include "toy/file/io/Base.hpp"

namespace toy{
namespace file{
namespace io{

class Standard : public Base
{
	public:

		Standard(){}
		virtual ~Standard(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual auto    read(void *file,uint32_t size)->uint32_t;
		virtual bool    write(const void *file,uint32_t size);
		virtual bool    seek(int option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd();
		virtual bool    isEmpty();

	private:

		std::FILE*   _file = nullptr;
		std::string  _path;
};

}}}
