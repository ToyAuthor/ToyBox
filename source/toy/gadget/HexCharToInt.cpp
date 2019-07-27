#include "toy/gadget/HexCharToInt.hpp"

#if TOY_OPTION_RELEASE
	#include "toy/Oops.hpp"
#else
	#include "toy/Exception.hpp"
#endif

namespace toy{
namespace gadget{

int HexCharToInt(const char code)
{
	if ( code<'0' )
	{
		#if TOY_OPTION_RELEASE
			toy::Oops(TOY_MARK);
			return 0;
		#else
			throw toy::Exception(TOY_MARK);
		#endif
	}
	else if ( code>'9' )
	{
		switch ( code )
		{
			case 'a': return 10;
			case 'A': return 10;
			case 'b': return 11;
			case 'B': return 11;
			case 'c': return 12;
			case 'C': return 12;
			case 'd': return 13;
			case 'D': return 13;
			case 'e': return 14;
			case 'E': return 14;
			case 'f': return 15;
			case 'F': return 15;
			default:
				#if TOY_OPTION_RELEASE
				{
					toy::Oops(TOY_MARK);
					return 0;
				}
				#else
					throw toy::Exception(TOY_MARK);
				#endif
		}
	}
	else
	{
		return code-'0';
	}

	return 0;
}

}}
