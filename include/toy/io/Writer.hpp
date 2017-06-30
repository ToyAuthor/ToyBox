
#pragma once

#include "toy/Standard.hpp"

/*
 * 1:Use standard library to save file.
 * 0:Support to save file with unicode name on Windows.
 */
#define TOY_OPTION_USE_STD_TEXT_OUTPUT_STREAM 0

#if TOY_OPTION_USE_STD_TEXT_OUTPUT_STREAM
	#include <fstream>
	namespace toy{
	namespace io{
		class Stream;
	}}
#else
	#include "toy/io/Stream.hpp"
#endif

namespace toy{
namespace io{

#if TOY_OPTION_USE_STD_TEXT_OUTPUT_STREAM
template<typename T=toy::io::Stream>
class Writer
{
	public:

		Writer(){}
		Writer(std::string filename){open(filename);}
		~Writer(){}

		bool open(std::string filename)
		{
			if ( boost::filesystem::exists( filename ) )
			{
				// No! Always open new one. Always!
				toy::Oops(TOY_MARK);
				return false;
			}

			_file.close();
			_file.open(filename);

			return true;
		}

		void newLine()
		{
			_file<<std::endl;
		}

		void print(std::string str)
		{
			_file<<str<<std::endl;
		}

		void printf(std::string str)
		{
			_file<<str;
		}

	private:

		std::ofstream   _file;
};
#else
template<typename T=toy::io::Stream>
class Writer
{
	public:

		Writer()
		{
			;
		}

		Writer(std::string filename)
		{
			if ( ! this->open(filename) )
			{
				toy::Oops(TOY_MARK);
			}
		}

		~Writer()
		{
			if ( _file.good() )
			{
				if ( ! _haveNewLine )
				{
					this->newLine();
				}
			}
		}

		bool open(std::string filename)
		{
			#ifdef TOY_WINDOWS
			if ( boost::filesystem::exists( toy::utf::UTF8ToWChar(filename) ) )
			#else
			if ( boost::filesystem::exists( filename ) )
			#endif
			{
				// No! Always open new one. Always!
				toy::Oops(TOY_MARK);
				return false;
			}

			_haveNewLine = false;
			_file.close();
			return _file.open(filename,"wb+");
		}

		void newLine()
		{
			if ( _file.good() )
			{
				//-------------LF-------------
				//char   newLineChar = '\n';
				//_file.write(&newLineChar,1);

				//-------------CR-------------
				//char   newLineChar = '\r';
				//_file.write(&newLineChar,1);

				//-------------CRLF-------------
				char   newLineChar[2] = {'\r','\n'};
				_file.write(newLineChar,2);

				_haveNewLine = true;
			}
		}

		void print(std::string str)
		{
			if ( _file.good() )
			{
				_file.write(str.c_str(),str.size());
				this->newLine();
			}
		}

		void printf(std::string str)
		{
			if ( _file.good() )
			{
				_file.write(str.c_str(),str.size());
				_haveNewLine = false;
			}
		}

	private:

		T               _file;
		bool            _haveNewLine = false;  // To make sure always have new line character at the end of file.
};
#endif
}
}
#undef TOY_OPTION_USE_STD_TEXT_OUTPUT_STREAM
