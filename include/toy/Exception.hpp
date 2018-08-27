
#pragma once

#include <stdexcept>
#include "toy/Mark.hpp"
#include "toy/MarkString.hpp"

namespace toy{

/*
 * Usage:
 *     throw toy::Exception(TOY_MARK);
 */
static inline std::runtime_error Exception(const char *file,int line)
{
	return std::runtime_error(toy::MarkString(file,line));
}

}
