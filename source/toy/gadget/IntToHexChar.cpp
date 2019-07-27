#include "toy/gadget/IntToHexChar.hpp"

#if TOY_OPTION_RELEASE
	#include "toy/Oops.hpp"
#else
	#include "toy/Exception.hpp"
#endif

namespace toy{
namespace gadget{

char IntToHexChar(int num)
{
	if ( num>15 || num<0 )
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
		case 10: return 'a';
		case 11: return 'b';
		case 12: return 'c';
		case 13: return 'd';
		case 14: return 'e';
		case 15: return 'f';
		default:
		#if TOY_OPTION_RELEASE
			toy::Oops(TOY_MARK);
		#else
			throw toy::Exception(TOY_MARK);
		#endif
	}

	return '0';
}

char IntToHexChar_Capital(int num)
{
	if ( num>15 || num<0 )
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
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
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
