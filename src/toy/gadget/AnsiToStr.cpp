#include "toy/gadget/AnsiToStr.hpp"
#include "toy/gadget/AnsiNumToStr.hpp"

namespace toy{
namespace gadget{

std::string AnsiToStr(char key)
{
	return AnsiNumToStr(static_cast<uint8_t>(key));
}

}}
