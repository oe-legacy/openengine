// Tests for display components.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>
#include "testDisplay.h"

#include <Core/GameEngine.h>
#include <Core/IModule.h>
#include "GameTestFactory.h"

// include display system
#include <Display/IFrame.h>

namespace OpenEngine {
namespace Tests {

using namespace std;
using namespace OpenEngine::Core;
using namespace OpenEngine::Display;

void testFrame() {
    // module to test frame after engine start
    class TestModule : public IModule {
        IGameEngine& engine;
        IFrame* frame;
    public:
        TestModule(IGameEngine& engine) : engine(engine) {}
        void Initialize() {
            // Check if a module of type IFrame has been loaded
            frame = dynamic_cast<IFrame*>(engine.Lookup(typeid(IFrame)));
            BOOST_CHECK(frame != NULL);
            // Set parameters before initialization (this should be supported)
            frame->SetWidth(800);
            frame->SetHeight(600);
            frame->SetDepth(32);
            frame->SetOptions(FrameOption(FRAME_NOBORDER | FRAME_FULLSCREEN));
        }
        void Process(const float dt, const float p) {
            // Check if Width is correct
            BOOST_CHECK(frame->GetWidth() == 800);
            // Check if Height is correct
            BOOST_CHECK(frame->GetHeight() == 600);
            // Check if Depth is correct
            BOOST_CHECK(frame->GetDepth() == 32);
            // Check if FRAME_FULLSCREEN and FRAME_NOBORDER is set
            BOOST_CHECK(frame->IsOptionSet(FRAME_FULLSCREEN));
            BOOST_CHECK(frame->IsOptionSet(FRAME_NOBORDER));
            // stop the engine
            engine.Stop();
        }
        void Deinitialize() {}
        bool IsTypeOf(const type_info& inf) { return false; }
    };
    // Create and start engine
    IGameEngine& engine = GameEngine::Instance();
    TestModule mod(engine);
    engine.AddModule(mod);
    engine.Start(GetTestFactory());
}

} // NS Tests
} // NS OpenEngine

