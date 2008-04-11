// Game Engine implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/GameEngine.h>
#include <Core/IGameFactory.h>
#include <Core/Exceptions.h>
#include <Logging/Logger.h>
#include <Utils/Timer.h>
#include <math.h>
#include <typeinfo>

namespace OpenEngine {
namespace Core {

using OpenEngine::Utils::Timer;
using namespace std;

/**
 * GameEngine constructor
 * Private because GameEngine is a singleton.
 *
 * @see GameEngine::Instance()
 */
GameEngine::GameEngine()
    : running(false), tick(50) {

}

/**
 * GameEngine destructor
 */
GameEngine::~GameEngine() {

}

/**
 * Get game engine instance.
 *
 * @return Reference to game engine instance
 */
IGameEngine& GameEngine::Instance() {
    if (instance == NULL)
        instance = new GameEngine();
    return *instance;
}

/**
 * Add a module to the engine.
 * No checking of existing modules is done so the same module can be
 * added many times.
 *
 * @param module Reference of module to add
 * @param flag Flag of the modules tick dependency
 */
void GameEngine::AddModule(IModule& module, const ProcessTick flag) {
    ((flag==TICK_DEPENDENT) ? dependent : independent).push_back(&module);
}

/**
 * Remove a module form the engine.
 * Only removes the first occurrence of the module in case of more
 * then one.
 *
 * @param module Reference of module to remove
 */
void GameEngine::RemoveModule(IModule& module) {
    list<IModule*>::iterator itr;
    for(itr=independent.begin(); itr!=independent.end(); ++itr){
        if( (*itr) == &module){
            independent.erase(itr);
            return;
        }
    }
    for(itr=dependent.begin(); itr!=dependent.end(); ++itr){
        if( (*itr) == &module){
            dependent.erase(itr);
            return;
        }
    }
}

/**
 * Find module by type.
 *
 * @param inf Type info of type to lookup
 * @return Pointer to a module of same type as \a search
 *         or \a NULL if module of type \a search is not found
 * @todo May throw exception
 */
IModule* GameEngine::Lookup(const type_info& inf) {
    // Iterate through list of modules
    list<IModule*>::iterator itr;
    for (itr=independent.begin(); itr!=independent.end(); ++itr) {
        if ((*itr)->IsTypeOf(inf)) {
            // Found the right Module type
            return *itr;
        }
    }
    for (itr=dependent.begin(); itr!=dependent.end(); ++itr) {
        if ((*itr)->IsTypeOf(inf)) {
            // Found the right Module type
            return *itr;
        }
    }
    // Requested type not in list.
    return NULL;
}

/**
 * Get the number of current modules in the engine.
 *
 * @return int Number of modules in engine
 */
int GameEngine::GetNumberOfModules() {
    return dependent.size() + independent.size();
}


/**
 * Initialize all modules.
 * Calls the initialize function on every module in the engine.
 *
 * @see IModule::Initialize()
 */
void GameEngine::InitModules() {
    list<IModule*>::iterator itr;
    for (itr=independent.begin(); itr != independent.end(); ++itr)
        (*itr)->Initialize();
    for (itr=dependent.begin(); itr != dependent.end(); ++itr)
        (*itr)->Initialize();
}

/**
 * Deinitialize all modules.
 * Calls the deinitialize function on every module in the engine.
 *
 * @see IModule::DeinitModules()
 */
void GameEngine::DeinitModules() {
    list<IModule*>::iterator itr;
    for (itr=independent.begin(); itr != independent.end(); ++itr)
        (*itr)->Deinitialize();
    for (itr=dependent.begin(); itr != dependent.end(); ++itr)
        (*itr)->Deinitialize();
    independent.clear();
    dependent.clear();
}

/**
 * Main game engine loop.
 * Built in accordance with the game loop described in [CTA 36].
 */
void GameEngine::StartGameLoop() {
    list<IModule*>::iterator itr;
    double time0;               // last time
    double time1;               // current time
    double timet;               // elapsed tick time
    float delta;                // elapsed time since last independent run
    int loops;

    // set starting times
    time0 = timet = Timer::GetTime();

    while (running) {

        // read elapsed time
        time1 = Timer::GetTime();

        // set the current elapsed time
        delta = (float) (time1 - time0);

        // if the tick time has elapsed run the dependent modules
        loops = 0;
        while ( (time1 - timet) > tick && loops < MAX_LOOPS ) {
            RunDependentModules(tick, 1);
            timet += tick;      // add a tick to the elapsed tick time
            ++loops;
        }

        // run the independent modules
        RunIndependentModules(delta, min(1.0f, (float)(time1 - timet) / tick));

        // update to the new last time
        time0 = time1;
    }
}

/**
 * Run all modules that are not dependent on the tick time.
 *
 * @param delta Delta time.
 * @param percent Percentage of current tick frame.
 */
void GameEngine::RunIndependentModules(const float delta, const float percent) {
    list<IModule*>::iterator itr;
    for (itr=independent.begin(); itr != independent.end(); ++itr)
        (*itr)->Process(delta, percent);   
}

/**
 * Run all modules that are dependent on the tick time.
 *
 * @param delta Delta time.
 * @param percent Percentage of current tick frame.
 */
void GameEngine::RunDependentModules(const float delta, const float percent) {
    list<IModule*>::iterator itr;
    for (itr=dependent.begin(); itr != dependent.end(); ++itr)
        (*itr)->Process(delta, percent);
}

float GameEngine::GetTickTime() {
    return tick;
}

void GameEngine::SetTickTime(const float time) {
    tick = time;
}

/**
 * Start is the recommended way of initializing and starting up
 * the engine. By supplying a GameFactory this method asks the
 * factory for basic modules like the Frame, SceneGraph and a
 * Renderer. They are all added to the engine, initialized and
 * the main game loop is started. All module creation and engine
 * setup is done by the GameFactory supplied.
 *
 * @param factory IGameFactory pointer to factory defining all setup.
 */
void GameEngine::Start(IGameFactory* factory) {
    if (running) {
        logger.warning << "Ignoring start request - engine already running." << logger.end;
        return;
    }
    // get all the required engine modules
    IFrame* frame = factory->GetFrame();
    IRenderer* renderer = factory->GetRenderer();

    // validate the modules
    bool fail = false;
    if (frame == NULL) {
        fail = true;
        logger.error << "Factory failed to supply a frame implementation - ";
    } 
    if (renderer == NULL) {
        fail = true;
        logger.error << "Factory failed to supply a renderer implementation - ";
    }
    if (fail) {
        logger.error << "aborting engine start." << logger.end;
        return;
    }
    // Add the frame to the engine.
    this->AddModule(*frame);

    // Call setup to add all other modules and do other setup.
    bool start = factory->SetupEngine(*this);

    // Check the renderer state and add it as the last module to the engine
    if (renderer->NumberOfRenderingViews() == 0) {
        logger.error << "No rendering views have been supplied to renderer." << logger.end;
        fail = true;
    }
    if (renderer->GetSceneRoot() == NULL) {
        logger.error << "No rendering scene has been supplied to renderer." << logger.end;
        fail = true;
    }
    if (fail) {
        logger.error << "Aborting engine start." << logger.end;
        return;
    }
    this->AddModule(*renderer);
    
    // If setup was successful start the engine.
    if (start) {
        running = true;
        InitModules();
        StartGameLoop();
        DeinitModules();
    } else logger.error << "Factory setup failed." << logger.end;
}

/**
 * @see IGameEngine::Stop()
 */
void GameEngine::Stop() {
    running = false;
}

} // NS Core
} // NS OpenEngine
