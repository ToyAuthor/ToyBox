#include "toy/Text.hpp"

namespace toy{

struct TextPrivate
{
	std::string   str;
};

}

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

uint32_t Text::size() const
{
	#if TOY_OPTION_CHECK
		if ( sizeof(std::string::size_type)>sizeof(uint32_t) )
		{
			if ( _this->str.size() > static_cast<std::string::size_type>(std::numeric_limits<uint32_t>::max()) )
			{
				toy::Oops(TOY_MARK);
			}
		}
	#endif

	return _this->str.size();
}

const char* Text::c_str() const
{
	return _this->str.c_str();
}

const std::string& Text::str() const
{
	return _this->str;
}
