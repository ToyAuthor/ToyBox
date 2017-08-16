#include "toy/Text.hpp"

namespace toy{

struct TextPrivate
{
	std::string   str;
};

}//namespace toy

using namespace toy;

Text::Text(std::string str):_this(new TextPrivate)
{
	_this->str = str;
}

Text::Text(const char* str):_this(new TextPrivate)
{
	_this->str = str;
}

Text::~Text()
{
	delete _this;
}

int Text::size()
{
	return (int)_this->str.size();
}

auto Text::c_str()->const char*
{
	return _this->str.c_str();
}
