
#pragma once

namespace toy{

enum Option:int
{
	_OPTION_START_OR_BEGIN = 0,
	NOTHING,
	WHATEVER,   // Default option.

	VERTEX_SHADER,
	FRAGMENT_SHADER,

	GL_1_1,
	GL_1_2,
	GL_1_3,
	GL_1_4,
	GL_1_5,
	GL_2_0,
	GL_2_1,
	GL_3_0,
	GL_3_1,
	GL_3_2,
	GL_3_3,
	GL_4_0,
	GL_4_1,
	GL_4_2,
	GL_4_3,
	GL_4_4,
	GL_4_5,

	GREY,        // 1 byte
	GREY_ALPHA,  // 2 byte
	RGB,         // 3 byte
	RGBA,        // 4 byte
};

}
