
#pragma once

#include "toy/Standard.hpp"

namespace toy{

struct TextPrivate;

class TOY_API Text
{
	public:

		Text(std::string str);
		Text(const char*);

		~Text();

		int  size();  // Not include null character.
		auto c_str()->const char*;
		auto cpp_str()->std::string;

	private:

		struct TextPrivate*   _this = nullptr;
};


}
