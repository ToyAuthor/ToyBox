
#pragma once

#include "toy/Standard.hpp"


namespace toy{
namespace file{
namespace io{


class Base
{
	public:

		Base(){}
		virtual ~Base(){}

		virtual bool    openDir(std::string path)=0;
		virtual bool    open(std::string filepath)=0;
		virtual auto    read(void *file,uint32_t size)->uint32_t = 0;
		virtual bool    write(void *file,uint32_t size)=0;
		virtual bool    isEnd()=0;
		virtual void    close()=0;
		virtual bool    isEmpty()=0;

		std::string getFileName()
		{
			if ( isEmpty() )
				return std::string();
			else
				return _fileName;
		}

		virtual bool    seek(int option,int32_t offset)=0;

	protected:

		std::string    _fileName;

};


}//namespace io
}//namespace file
}//namespace toy
