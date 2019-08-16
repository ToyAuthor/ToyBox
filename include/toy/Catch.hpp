
#pragma once

#include <exception>
#include "toy/CompilerConfig.hpp"
#include "toy/ErrorTag.hpp"

namespace toy{

// Implement at toy/Throw.hpp
TOY_API extern auto Catch(std::exception &)-> ::toy::ErrorTag;
TOY_API extern auto Catch_ForTest(std::exception &)-> ::toy::ErrorTag;

}
