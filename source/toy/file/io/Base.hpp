
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

		virtual bool    OpenDir(std::string path)=0;                // Open up a directory or archive.
		virtual bool    Open(std::string filepath)=0;
		virtual bool    Read(void *file,uint32_t size)=0;           // As some as ::fread().
		virtual bool    Write(void *file,uint32_t size)=0;
		virtual void    Close()=0;
		virtual bool    IsEmpty()=0;

		std::string GetFileName()
		{
			if(IsEmpty())
				return std::string();
			else
				return mFileName;
		}

		virtual bool    Seek(enum Option option,int32_t offset)=0;    // As some as ::fseek().
		virtual void*   GetFilePointer()=0;// Bad design

	protected:

		std::string          mFileName;      ///< Write down the file name.

};


}//namespace io
}//namespace file
}//namespace toy
