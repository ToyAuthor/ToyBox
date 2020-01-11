
#pragma once

#include <string>

static inline std::string GetPrefix()
{
	return std::string("toy_");
}

static inline std::string GetPrefixPrivate()
{
	return std::string("_toy_");
}

static inline std::string GetConstPrefix()
{
	return std::string("TOY_");
}

static inline std::string GetConstPrefixPrivate()
{
	return std::string("_TOY_");
}
