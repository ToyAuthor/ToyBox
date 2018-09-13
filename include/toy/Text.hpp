
#pragma once

#include "toy/Standard.hpp"

namespace toy{

struct TextPrivate;

class TOY_API Text
{
	public:

		Text(std::string str);
		Text(const char* str);

		~Text();

		auto size() const -> uint32_t;          // Not include null character.
		auto c_str() const -> const char*;
		auto str() const -> const std::string&;

	private:

		struct TextPrivate*   _this = nullptr;
};

}
