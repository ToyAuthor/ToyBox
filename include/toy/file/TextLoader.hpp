
#pragma once

#include "toy/Standard.hpp"

namespace toy{
namespace file{


struct TextLoaderPrivate;

/// Loading text file line by line.
class TOY_API TextLoader
{
	public:

		TextLoader();
		TextLoader(std::string filename);

		~TextLoader();

		bool    LoadText(std::string filename);     // Loading a text file.
		bool    LoadText(char *buffer,int size);    // Loading a text from memory.(copy)
		bool    NextLine(std::string &str);         // Same as std::getline().

	private:

		std::unique_ptr<TextLoaderPrivate>   mThis;
};



}//namespace file
}//namespace toy
