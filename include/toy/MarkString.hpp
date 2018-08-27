
#pragma once

#include <string>

namespace toy{

static inline std::string MarkString(const char *file,int line)
{
	char        buffer[6];
	const char  ff = '0';
	int         bu[5];
	int         temp1 = line%100;
	int         temp2 = line%10;

	bu[4] = temp2;
	bu[3] = (temp1 - temp2)/10;       temp2 = line%1000;
	bu[2] = (temp2 - temp1)/100;      temp1 = line%10000;
	bu[1] = (temp1 - temp2)/1000;     temp2 = line%100000;
	bu[0] = (temp2 - temp1)/10000;

	buffer[5] = '\0';
	buffer[4] = ff + bu[4];
	buffer[3] = ff + bu[3];
	buffer[2] = ff + bu[2];
	buffer[1] = ff + bu[1];
	buffer[0] = ff + bu[0];

	return std::string(file) + ":" + buffer;
}

/*
#include <sstream>

static inline std::string MarkString(const char *file,int line)
{
	std::stringstream ss;
	ss<<file;
	ss<<line;

	std::string str;
	ss>>str;

	return str;
}*/

}
