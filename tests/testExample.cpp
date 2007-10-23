// Test case example
//
// test howto:
// 1. write your test functions in yourTestFile.cpp
// 2. define it in yourTestFile.h
// 3. include the header in test_suite.h
// 4. add the test method in test_suite.cpp
//
// -------------------------------------------------------------------
// Copyright (C) 2007 daimi.au.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>

// include test header
#include "testExample.h"

// create test function
void OpenEngine::Tests::testExample() {

    // boolean check, continues on error
    BOOST_CHECK(1 == 1);

    // boolean check, halts on error
    BOOST_REQUIRE(2 == 2);

}
