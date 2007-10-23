// Game engine testing implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "GameTestFactory.h"

// interface implementations
#include <Core/IGameFactory.h>
#include <Display/SDLFrame.h>
#include <Display/Viewport.h>
#include <Display/ViewingVolume.h>
#include <Devices/SDLInput.h>
#include <Renderers/OpenGL/Renderer.h>
#include <Renderers/OpenGL/RenderingView.h>
#include <Scene/SceneNode.h>


// INCLUDE YOUR GAME FACTORY FILE HERE
// #include "path/to/MyGameFactory.h"


namespace OpenEngine {
namespace Tests {

using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Devices;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Renderers;
using namespace OpenEngine::Renderers::OpenGL;
using namespace OpenEngine::Scene;


/**
 * Stub test factory.
 * You may include and supply your own factory to test your game with
 * the test cases by changing the return value of GetTestFactory.
 */
class GameTestFactory : public IGameFactory {
public:
    IFrame*      frame;
    IRenderer*   renderer;
    GameTestFactory() {
        frame    = new SDLFrame(800, 600, 32);
        Viewport* viewport = new Viewport(*frame);
        viewport->SetViewingVolume(new ViewingVolume());
        renderer = new Renderer();
        renderer->AddRenderingView(new RenderingView(*viewport));
        renderer->SetSceneRoot(new SceneNode());
    }
    bool SetupEngine(IGameEngine& engine) {
        // Setup input handling
        SDLInput* input = new SDLInput();
        engine.AddModule(*input);
        // Return true to signal success.
        return true;
    }
    IFrame*      GetFrame()      { return frame; }
    IRenderer*   GetRenderer()   { return renderer; }
};

/**
 * Get the factory to use in the tests.
 */
IGameFactory* GetTestFactory() {

    // CHANGE THIS TO AN INSTANCE OF YOUR GAME FACTORY
    // return new MyGameFactory();
    return new GameTestFactory();

}

} // NS Tests
} // NS OpenEngine
