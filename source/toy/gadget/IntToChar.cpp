#include "toy/gadget/IntToChar.hpp"

#if TOY_OPTION_RELEASE
	#include "toy/Oops.hpp"
#else
	#include "toy/Exception.hpp"
#endif

namespace toy{
namespace gadget{

char IntToChar(int num)
{
	if ( num>9 || num<0 )
	{
		#if TOY_OPTION_RELEASE
			toy::Oops(TOY_MARK);
			return '0';
		#else
			throw toy::Exception(TOY_MARK);
		#endif
	}

	switch ( num )
	{
		case  0: return '0';
		case  1: return '1';
		case  2: return '2';
		case  3: return '3';
		case  4: return '4';
		case  5: return '5';
		case  6: return '6';
		case  7: return '7';
		case  8: return '8';
		case  9: return '9';
		default:
		#if TOY_OPTION_RELEASE
			toy::Oops(TOY_MARK);
		#else
			throw toy::Exception(TOY_MARK);
		#endif
	}

	return '0';
}

}}
