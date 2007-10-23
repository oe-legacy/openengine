// Test the resource system.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>

#include "testResources.h"

// include resources lib
#include <Resources/File.h>

namespace OpenEngine {
namespace Tests {

using namespace OpenEngine::Resources;

void testFile() {

    // test parent
    BOOST_CHECK(File::Parent("/a/b/c") == "/a/b/");
    BOOST_CHECK(File::Parent("/a/b/")  == "/a/");
    BOOST_CHECK(File::Parent("/a")     == "/");
    BOOST_CHECK(File::Parent("")       == "");
    BOOST_CHECK(File::Parent("a")      == "");
    // test extension
    BOOST_CHECK(File::Extension("/a/b/c.d")   == "d");
    BOOST_CHECK(File::Extension("/a/b/c.d.e") == "e");
    BOOST_CHECK(File::Extension("/a/b/c.")    == "");
    BOOST_CHECK(File::Extension("/a/b/c")     == "");
    BOOST_CHECK(File::Extension("/file.ext")  == "ext");
    BOOST_CHECK(File::Extension("")           == "");
}

} // NS Tests
} // NS OpenEngine
