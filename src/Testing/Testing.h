// Testing utilities
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_TESTING_H_
#define _OE_TESTING_H_

// This file simple wraps the boost minimal testing macros

#include <boost/test/minimal.hpp>

#define OE_CHECK   BOOST_CHECK
#define OE_REQUIRE BOOST_REQUIRE
#define OE_ERROR   BOOST_ERROR
#define OE_FAIL    BOOST_FAIL
#define OE_CHECK_THROW(exp, exc)                \
    try { exp; BOOST_ERROR("test "#exp" did not throw "#exc); } catch (exc&) {}

#endif // _OE_TESTING_H_
