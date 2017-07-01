
#pragma once

#include <string>

inline std::string GetPrefix()
{
	return std::string("Toy_");
}

inline std::string GetPrefixPrivate()
{
	return std::string("__toy__");
}
