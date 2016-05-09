
#pragma once

#include <cstdio>
#include "toy/file/io/Base.hpp"

namespace toy{
namespace file{
namespace io{


class Standard : public Base
{
	public:

		Standard(){}
		virtual ~Standard(){Close();}

		virtual bool    OpenDir(std::string path);
		virtual bool    Open(std::string filepath);
		virtual bool    Read(void *file,uint32_t size);
		virtual bool    Write(void *file,uint32_t size);
		virtual bool    Seek(enum Base::Option option,int32_t offset);
		virtual void    Close();
		virtual bool    IsEmpty();
		virtual void*   GetFilePointer();

	private:

		FILE*        mFile = nullptr;
		std::string  mPath;
};


}//namespace io
}//namespace file
}//namespace toy
