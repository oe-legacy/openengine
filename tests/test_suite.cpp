// The OpenEngine test suite
//
// After defining test files in test_suite.h add the tests with:
//   test->add( BOOST_TEST_CASE( &my_test_function ) );
// 
// See testExample.* on how to add a test.
// -------------------------------------------------------------------
// Copyright (C) 2007 daimi.au.dk (See AUTHORS) 
//
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (LICENSE). 
//--------------------------------------------------------------------

#include <string>

// Needed to run under Mac OS X
#include <Meta/SDL.h>

#include <boost/version.hpp>

#ifndef _WIN32
    #if BOOST_VERSION / 100 % 1000 >= 34
    #define BOOST_TEST_NO_MAIN
    #define BOOST_TEST_DYN_LINK
    #endif
#endif

#include <boost/test/unit_test.hpp>

#if __APPLE__
#include <boost/test/impl/unit_test_main.ipp>
#endif

#include "test_suite.h"

// logging
#include <Logging/Logger.h>
#include <Logging/StreamLogger.h>

using boost::unit_test::test_suite;
using std::string;
using namespace OpenEngine::Tests;
using namespace OpenEngine::Logging;

const int AUTO_TESTS = 1;
const int MANUAL_TESTS = 2;

test_suite* init_unit_test_suite( int argc, char* argv[] ) {

    // Uncomment this line to enable log output.
    Logger::AddLogger(new StreamLogger(&std::cout));

    int type = AUTO_TESTS + MANUAL_TESTS;
    if (argc > 1) {
        if (string(argv[1])=="auto")   type = AUTO_TESTS;
        if (string(argv[1])=="manual") type = MANUAL_TESTS;
    }
    test_suite* test = BOOST_TEST_SUITE( "engine test suite" );
    if (type & AUTO_TESTS) {
        // add automatic tests here
        test->add( BOOST_TEST_CASE(&testExample) );
        // math tests
        test->add( BOOST_TEST_CASE(&testVector) );
        test->add( BOOST_TEST_CASE(&testMatrix) );
        test->add( BOOST_TEST_CASE(&testQuaternion) );
        // geometry tests
        test->add( BOOST_TEST_CASE(&testFaceSet) );
        test->add( BOOST_TEST_CASE(&testLine) );
        // Test GameEngine
        test->add( BOOST_TEST_CASE(&testAddRemoveModules) );
        test->add( BOOST_TEST_CASE(&testInitDeinitModules) );
        test->add( BOOST_TEST_CASE(&testGameEngineLookup) );
        // Test Events and Listeners
        test->add( BOOST_TEST_CASE(&testEventListeners) );
        test->add( BOOST_TEST_CASE(&testQueuedEventListeners) );
        // Test Display
        test->add( BOOST_TEST_CASE(&testFrame) );
        // Test resource system
        test->add( BOOST_TEST_CASE(&testFile) );
        // Test OBJ loader 
        test->add( BOOST_TEST_CASE(&testOBJModelResource) );
        // Scene tests
        test->add( BOOST_TEST_CASE(&testSceneDelete) );
        test->add( BOOST_TEST_CASE(&testSceneClone) );
        test->add( BOOST_TEST_CASE(&testSceneReplace) );
        test->add( BOOST_TEST_CASE(&testSceneRemove) );
    }
    if (type & MANUAL_TESTS) {
        // add manual tests here
        test->add( BOOST_TEST_CASE(&testKeyboard) );
        test->add( BOOST_TEST_CASE(&testMouse) );
    }
    return test;
}

#ifdef BOOST_TEST_NO_MAIN
int argc_hack;
char** argv_hack;
bool boost_hack() {
    boost::unit_test::framework::master_test_suite().p_name.value = "test";
    boost::unit_test::framework::master_test_suite().add(init_unit_test_suite (argc_hack, argv_hack));
	return true;
}
int main( int argc, char* argv[] ) {
    argc_hack = argc;
    argv_hack = argv;
    return boost::unit_test::unit_test_main( &boost_hack, argc, argv );
}
#endif
