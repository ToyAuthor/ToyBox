#include "toy/gadget/CharToInt.hpp"

#if TOY_OPTION_RELEASE
	#include "toy/Oops.hpp"
#else
	#include "toy/Exception.hpp"
#endif

namespace toy{
namespace gadget{

int CharToInt(const char code)
{
	if ( code<'0' || code>'9' )
	{
		#if TOY_OPTION_RELEASE
			toy::Oops(TOY_MARK);
			return 0;
		#else
			throw toy::Exception(TOY_MARK);
		#endif
	}

	return code-'0';
}

}}
