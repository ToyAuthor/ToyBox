#include "toy/gadget/StrToAscii.hpp"

#if TOY_OPTION_RELEASE
	#include "toy/Oops.hpp"
#else
	#include "toy/Exception.hpp"
#endif

namespace toy{
namespace gadget{

char StrToAscii(const char *source)
{
	return StrToAscii(std::string(source));
}

static inline char HandleLastPart(const std::string & key)
{
	if      ( key == "A" ) return 65;
	else if ( key == "B" ) return 66;
	else if ( key == "C" ) return 67;
	else if ( key == "D" ) return 68;
	else if ( key == "E" ) return 69;
	else if ( key == "F" ) return 70;
	else if ( key == "G" ) return 71;
	else if ( key == "H" ) return 72;
	else if ( key == "I" ) return 73;
	else if ( key == "J" ) return 74;
	else if ( key == "K" ) return 75;
	else if ( key == "L" ) return 76;
	else if ( key == "M" ) return 77;
	else if ( key == "N" ) return 78;
	else if ( key == "O" ) return 79;
	else if ( key == "P" ) return 80;
	else if ( key == "Q" ) return 81;
	else if ( key == "R" ) return 82;
	else if ( key == "S" ) return 83;
	else if ( key == "T" ) return 84;
	else if ( key == "U" ) return 85;
	else if ( key == "V" ) return 86;
	else if ( key == "W" ) return 87;
	else if ( key == "X" ) return 88;
	else if ( key == "Y" ) return 89;
	else if ( key == "Z" ) return 90;

	else
	{
		#if TOY_OPTION_RELEASE
			toy::Oops(TOY_MARK);
		#else
			throw toy::Exception(TOY_MARK);
		#endif
	}

	return 42;
}

char StrToAscii(const std::string & key)
{
	if      ( key == "[Space]" ) return 32;

	else if ( key == "[DEL]" ) return 127;
	else if ( key == "[NUL]" ) return 0;
	else if ( key == "[SOH]" ) return 1;
	else if ( key == "[STX]" ) return 2;
	else if ( key == "[ETX]" ) return 3;
	else if ( key == "[EOT]" ) return 4;
	else if ( key == "[ENQ]" ) return 5;
	else if ( key == "[ACK]" ) return 6;
	else if ( key == "[BEL]" ) return 7;
	else if ( key == "[BS]"  ) return 8;
	else if ( key == "[TAB]" ) return 9;
	else if ( key == "[LF]"  ) return 10;
	else if ( key == "[VT]"  ) return 11;
	else if ( key == "[FF]"  ) return 12;
	else if ( key == "[CR]"  ) return 13;
	else if ( key == "[SO]"  ) return 14;
	else if ( key == "[SI]"  ) return 15;
	else if ( key == "[DLE]" ) return 16;
	else if ( key == "[DC1]" ) return 17;
	else if ( key == "[DC2]" ) return 18;
	else if ( key == "[DC3]" ) return 19;
	else if ( key == "[DC4]" ) return 20;
	else if ( key == "[NAK]" ) return 21;
	else if ( key == "[SYN]" ) return 22;
	else if ( key == "[ETB]" ) return 23;
	else if ( key == "[CAN]" ) return 24;
	else if ( key == "[EM]"  ) return 25;
	else if ( key == "[SUB]" ) return 26;
	else if ( key == "[ESC]" ) return 27;
	else if ( key == "[FS]"  ) return 28;
	else if ( key == "[GS]"  ) return 29;
	else if ( key == "[RS]"  ) return 30;
	else if ( key == "[US]"  ) return 31;

	else if ( key == "!" ) return 33;
	else if ( key == "\"") return 34;
	else if ( key == "#" ) return 35;
	else if ( key == "$" ) return 36;
	else if ( key == "%" ) return 37;
	else if ( key == "&" ) return 38;
	else if ( key == "'" ) return 39;
	else if ( key == "(" ) return 40;
	else if ( key == ")" ) return 41;
	else if ( key == "*" ) return 42;
	else if ( key == "+" ) return 43;
	else if ( key == "," ) return 44;
	else if ( key == "-" ) return 45;
	else if ( key == "." ) return 46;
	else if ( key == "/" ) return 47;
	else if ( key == ":" ) return 58;
	else if ( key == ";" ) return 59;
	else if ( key == "<" ) return 60;
	else if ( key == "=" ) return 61;
	else if ( key == ">" ) return 62;
	else if ( key == "?" ) return 63;
	else if ( key == "@" ) return 64;
	else if ( key == "[" ) return 91;
	else if ( key == "\\") return 92;
	else if ( key == "]" ) return 93;
	else if ( key == "^" ) return 94;
	else if ( key == "_" ) return 95;
	else if ( key == "`" ) return 96;
	else if ( key == "{" ) return 123;
	else if ( key == "|" ) return 124;
	else if ( key == "}" ) return 125;
	else if ( key == "~" ) return 126;

	else if ( key == " " ) return 32;
	else if ( key == "0" ) return 48;
	else if ( key == "1" ) return 49;
	else if ( key == "2" ) return 50;
	else if ( key == "3" ) return 51;
	else if ( key == "4" ) return 52;
	else if ( key == "5" ) return 53;
	else if ( key == "6" ) return 54;
	else if ( key == "7" ) return 55;
	else if ( key == "8" ) return 56;
	else if ( key == "9" ) return 57;

	else if ( key == "a" ) return 97;
	else if ( key == "b" ) return 98;
	else if ( key == "c" ) return 99;
	else if ( key == "d" ) return 100;
	else if ( key == "e" ) return 101;
	else if ( key == "f" ) return 102;
	else if ( key == "g" ) return 103;
	else if ( key == "h" ) return 104;
	else if ( key == "i" ) return 105;
	else if ( key == "j" ) return 106;
	else if ( key == "k" ) return 107;
	else if ( key == "l" ) return 108;
	else if ( key == "m" ) return 109;
	else if ( key == "n" ) return 110;
	else if ( key == "o" ) return 111;
	else if ( key == "p" ) return 112;
	else if ( key == "q" ) return 113;
	else if ( key == "r" ) return 114;
	else if ( key == "s" ) return 115;
	else if ( key == "t" ) return 116;
	else if ( key == "u" ) return 117;
	else if ( key == "v" ) return 118;
	else if ( key == "w" ) return 119;
	else if ( key == "x" ) return 120;
	else if ( key == "y" ) return 121;
	else if ( key == "z" ) return 122;

	return HandleLastPart(key);
}

}}
