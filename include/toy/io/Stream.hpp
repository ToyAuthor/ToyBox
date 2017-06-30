
#pragma once

#include "toy/Environment.hpp"
#include "toy/Mark.hpp"
#include "toy/Log.hpp"

#ifdef TOY_WINDOWS
	#include <wchar.h>
	#include "toy/Utf.hpp"
#endif

namespace toy{
namespace io{

// A wrapper of <stdio.h> and supporting utf-8 encoding.
class Stream
{
	public:

		Stream()
		{
			;
		}

		Stream(std::string filename,std::string option)
		{
			if ( ! this->open(filename,option) )
			{
				_file = nullptr;
			}
		}

		bool isEmpty()
		{
			if ( _file==nullptr )
				return true;
			else
				return false;
		}

		bool good()
		{
			return ! this->isEmpty();
		}

		~Stream()
		{
			this->close();
		}

		bool open(std::string filename,std::string option)
		{
			this->close();

			#ifdef TOY_WINDOWS
				auto   wfilename = toy::utf::UTF8ToWChar(filename);
				auto   woption   = toy::utf::UTF8ToWChar(option);
				_file = ::_wfopen(wfilename.c_str(),woption.c_str());
			#elif defined(TOY_ANDROID)
				_file = fopen(filename.c_str(),option.c_str());
			#else
				_file = std::fopen(filename.c_str(),option.c_str());
			#endif

			if ( _file )
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		uint32_t read(void *ptr,uint32_t size)
		{
			if ( isEmpty() )
			{
				toy::Oops(TOY_MARK);
				return 0;
			}

			#if defined(TOY_ANDROID)
			uint32_t	result = fread(ptr,1,(size_t)size,_file);
			#else
			uint32_t	result = std::fread(ptr,1,(size_t)size,_file);
			#endif

			if ( result>size )
			{
				toy::Oops(TOY_MARK);
				return 0;
			}

			return result;
		}

		bool write(const void *ptr,uint32_t size)
		{
			if ( this->isEmpty() )
			{
				toy::Oops(TOY_MARK);
				return false;
			}

			#if defined(TOY_ANDROID)
			fwrite(ptr,(size_t)size,1,_file);
			#else
			std::fwrite(ptr,(size_t)size,1,_file);
			#endif
			return true;
		}

		bool isEnd()
		{
			if ( this->isEmpty() )
			{
				toy::Oops(TOY_MARK);
				return true;
			}

			#if defined(TOY_ANDROID)
			if ( feof(_file) )
			#else
			if ( std::feof(_file) )
			#endif
			{
				return true;
			}

			return false;
		}

		void close()
		{
			if ( _file )
			{
				#if defined(TOY_ANDROID)
				fclose(_file);
				#else
				std::fclose(_file);
				#endif
				_file = nullptr;
			}
		}

		bool seek(int option,int32_t offset)
		{
			if ( this->isEmpty() )
			{
				toy::Oops(TOY_MARK);
				return false;
			}

			#if TOY_OPTION_CHECK_CAREFUL
				switch ( option )
				{
					case SEEK_SET:
					case SEEK_CUR:
					case SEEK_END:
						break;
					default:
						toy::Oops(TOY_MARK);
				}
			#endif

			#if defined(TOY_ANDROID)
			fseek( _file, offset, option );
			#else
			std::fseek( _file, offset, option );
			#endif

			return true;
		}

	private:

		FILE*      _file = nullptr;
};



}}
