
#pragma once

namespace toy{

enum Option:int
{
	_OPTION_START_OR_BEGIN = 0,
	NOTHING,


	WHATEVER,


	GREY,        // 1 byte
	GREY_ALPHA,  // 2 byte
	RGB,         // 3 byte
	RGBA,        // 4 byte
};

}
