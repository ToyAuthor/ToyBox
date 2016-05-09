#include <fstream>
#include <sstream>
#include <iostream>
#include "toy/file/TextLoader.hpp"

//--------------------boost--------------------start
#if TOY_OPTION_ENABLE_BOOST

	//#ifdef TOY_WINDOWS
		// Following warning will be output, if you don't define it.
		// warning: 'boost::system::generic_category' defined but not used
		#ifndef BOOST_SYSTEM_NO_DEPRECATED
		#define BOOST_SYSTEM_NO_DEPRECATED 1
		#endif
	//#endif

	#include "boost/filesystem.hpp"

#endif
//--------------------boost--------------------end


namespace toy{
	namespace file{
		struct TextLoaderPrivate{
			int                mLineNumber;
			std::stringstream  mStream;
		};
	}
}


using namespace toy;
using namespace file;


TextLoader::TextLoader():mThis(new TextLoaderPrivate)
{
	;
}

TextLoader::TextLoader(std::string filename):mThis(new TextLoaderPrivate)
{
	LoadText(filename);
}

TextLoader::~TextLoader()
{
	;
}

static inline void CleanStringStream(std::stringstream &ss)
{
	ss.clear();
	ss.str("");
}

bool TextLoader::LoadText(std::string filename)
{
	#if TOY_OPTION_ENABLE_BOOST
		if ( !boost::filesystem::exists( filename.c_str() ) )
		{
			// Can't find this file!
			toy::Oops(TOY_MARK);
			return 0;
		}
	#endif

	std::ifstream    file(filename.c_str());

	if( ! file.good() )
	{
		toy::Oops(TOY_MARK);   // Can't find this file!
		return 0;
	}

	CleanStringStream(mThis->mStream);

	mThis->mStream << file.rdbuf();
	mThis->mLineNumber=0;

	return 1;
}

bool TextLoader::LoadText(char *buffer,int size)
{
	std::istringstream    stream;

	stream.rdbuf()->pubsetbuf(buffer,size);

	CleanStringStream(mThis->mStream);
	mThis->mStream << stream.rdbuf();
	mThis->mLineNumber=0;

	return 1;
}

bool TextLoader::NextLine(std::string &str)
{
	mThis->mLineNumber++;

	std::string   buffer;

	// I have better replace std::getline() by fgets(). It's much safe.
	if( std::getline(mThis->mStream,buffer) )
	{
		str = buffer.c_str();
		return (bool)1;
	}
	else
	{
		return (bool)0;  // return 0, if no next line.
	}
}
