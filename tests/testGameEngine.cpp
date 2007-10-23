// -------------------------------------------------------------------
// Copyright (C) 2007 daimi.au.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>
#include "testGameEngine.h"

#include <Core/GameEngine.h>
#include "GameTestFactory.h"
#include <Core/IModule.h>

namespace OpenEngine {
namespace Tests {

using namespace OpenEngine::Core;

class TestModule : public IModule {
public:
    int processCount;
    bool initOK;
    bool deinitOK;
    TestModule() {
        processCount = 0;
        initOK = deinitOK = false;
    }
    ~TestModule() {}
    void Initialize() {
        initOK = true;
    }
    void Process(const float deltaTime, const float percent) {
        IGameEngine::Instance().Stop();
    }
    void Deinitialize() {
        deinitOK = true;
    }
    bool IsTypeOf(const std::type_info& inf) {
        return typeid(TestModule) == inf;
    }
};

// Test AddModule() and RemoveModule()
void testAddRemoveModules(){
    // Create test GameEngine
    IGameEngine& engine = GameEngine::Instance();

    // Create test module
    TestModule m1;
    // Add module
    engine.AddModule(m1);
    // Test if the module was added
    BOOST_CHECK(engine.GetNumberOfModules() == 1);
    // Remove module
    engine.RemoveModule(m1);
    // Test if the module was removed
    BOOST_CHECK(engine.GetNumberOfModules() == 0);

    // Create another module
    TestModule m2;
    // Add module m1
    engine.AddModule(m1);
    // Try remove non-existing module
    engine.RemoveModule(m2);
    // Test
    BOOST_CHECK(engine.GetNumberOfModules() == 1);
    // Remove last
    engine.RemoveModule(m1);

    // Create another module
    TestModule m3;
    // Add module m3 twice
    engine.AddModule(m3);
    engine.AddModule(m3);
    engine.AddModule(m3);
    // Remove only one module
    engine.RemoveModule(m3);
    // Test
    BOOST_CHECK(engine.GetNumberOfModules() == 2);
    // Remove the last 2
    engine.RemoveModule(m3);
    engine.RemoveModule(m3);
    // Test for empty list
    BOOST_CHECK(engine.GetNumberOfModules() == 0);
}

// Test InitModules() and DeinitModules()
void testInitDeinitModules() {
    // Create test GameEngine
    IGameEngine& engine = GameEngine::Instance();

    // Create test module
    TestModule m1;
    // Add module
    engine.AddModule(m1);

    // Start the engine - the TestModule will flag shutdown
    engine.Start(GetTestFactory());

    // Test init
    BOOST_CHECK(m1.initOK = true);
    // Test deinit
    BOOST_CHECK(m1.deinitOK = true);

    // Clean up
    engine.RemoveModule(m1);
}

// Test Module Process(float timeStep)
void testModuleProcess() {}


// Test GameEngine Lookup.
void testGameEngineLookup() {
    // Create test GameEngine
    IGameEngine& engine = GameEngine::Instance();

    // Create test module
    TestModule* m1 = new TestModule();
    m1->processCount = 42;
    // Add module
    engine.AddModule(*m1);

    // Try lookup
    IModule* res = engine.Lookup(typeid(TestModule));
    // Check result
    BOOST_REQUIRE(res != NULL);

    TestModule* test = dynamic_cast<TestModule*>(res);
    BOOST_REQUIRE(test != NULL);

    // Check it's actually the right module
    BOOST_CHECK(test->processCount == 42);

    // Clean up
    engine.RemoveModule(*m1);
    delete m1;
}

} // NS Tests
} // NS OpenEngine
