
#pragma once

#include "toy/Standard.hpp"


namespace toy{
namespace file{
namespace io{


class Base
{
	public:

		/// Options of Seek().
		enum Option
		{
			SET=0,      // Seek from the head of file.
			END,        // Seek from the end of file.
			CUR,        // Seek from the pointer of file.
		};

		Base(){}
		virtual ~Base(){}

		virtual bool    openDir(std::string path)=0;                // Open up a directory or archive.
		virtual bool    open(std::string filepath)=0;
		virtual int     read(void *file,uint32_t size)=0;           // As some as ::fread().
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

		virtual bool    seek(enum Option option,int32_t offset)=0;    // Some as ::fseek().
		virtual void*   getFilePointer()=0;// Bad design

	protected:

		std::string    _fileName;

};


}//namespace io
}//namespace file
}//namespace toy
