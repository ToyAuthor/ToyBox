
#pragma once

#include "toy/CompilerConfig.hpp"
#include "toy/Mark.hpp"
#include "toy/ErrorTag.hpp"

namespace toy{

TOY_API extern void Throw(const char *file,int line, enum ::toy::ErrorTag tag);

}
