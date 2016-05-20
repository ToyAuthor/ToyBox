
#pragma once

#ifdef TOY_MARK
	#error "TOY_MARK already exist"
#else
	#define TOY_MARK __FILE__,__LINE__
#endif
