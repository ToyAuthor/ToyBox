
#pragma once

#include <memory>
#include <cstdint>

namespace toy{
namespace archive{

struct Config
{
	bool                                   isSingleFile = false;
	bool                                   isHaveMD5 = false;
	bool                                   isMultiVolume = false;
};

}}
