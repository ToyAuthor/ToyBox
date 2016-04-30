
#pragma once

#if defined(TOY_MARK)
	#error "TOY_MARK already have"
#endif

/*
Some of compiler don't have "__FUNCTION__".
__FUNCTION__
__FUNCDNAME__
__FUNCSIG__
__PRETTY_FUNCTION__
__func__
__DATE__
__TIME__
*/

#define TOY_MARK __FILE__,__LINE__
