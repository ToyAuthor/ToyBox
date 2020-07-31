#include "toy/gadget/CharToInt.hpp"
#include "toy/Ooops.hpp"

namespace toy{
namespace gadget{

int CharToInt(const char code)
{
	if ( code<'0' || code>'9' )
	{
		toy::Ooops(TOY_MARK);
		return 0;
	}

	return code-'0';
}

}}
