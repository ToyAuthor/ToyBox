#include <algorithm>
#include "toy/gadget/StringExt.hpp"

namespace toy{
namespace gadget{

std::string Reverse(const std::string &str)
{
	std::string clone(str);
	std::reverse(clone.begin(), clone.end());

	return clone;
}

}}
