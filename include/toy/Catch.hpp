// Implement at toy/Throw.hpp

#pragma once

#include <exception>
#include "toy/CompilerConfig.hpp"
#include "toy/ErrorTag.hpp"

namespace toy{

TOY_API extern auto Catch(std::exception &)-> ::toy::ErrorTag;
TOY_API extern auto Catch_ForTest(std::exception &)-> ::toy::ErrorTag;

}
