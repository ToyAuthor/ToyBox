
#pragma once


// Following warning will be output, if you don't define this macro.
// warning: 'boost::system::generic_category' defined but not used
#ifndef BOOST_SYSTEM_NO_DEPRECATED
#define BOOST_SYSTEM_NO_DEPRECATED 1
#endif

// Disable auto link.
#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

#include "boost/filesystem.hpp"
