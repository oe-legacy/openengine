// Game Engine implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <Core/IGameEngine.h>
#include <list>
#include <typeinfo>

namespace OpenEngine {
namespace Core {

using std::type_info;
using std::list;

/**
 * Game Engine implementation.
 * Acts as game module container responsible for performing
 * initialization and deinitialization tasks.
 * Follows the singelton pattern.
 *
 * @class GameEngine GameEngine.h Core/GameEngine.h
 */
class GameEngine : public IGameEngine {
private:

    // Engine running flag
    bool running;

    // Tick time for dependent modules
    float tick;

    // Maximum iterations to perform for tick dependent modules.
    static const int MAX_LOOPS = 10;

    // Lists for engine modules
    list<IModule*> dependent;
    list<IModule*> independent;

    GameEngine();
    void InitModules();
    void DeinitModules();
    void StartGameLoop();
    void RunIndependentModules(const float delta, const float percent);
    void RunDependentModules(const float delta, const float percent);

public:

    static IGameEngine& Instance();
    ~GameEngine();

    float GetTickTime();
    void SetTickTime(const float time);

    void AddModule(IModule& module, const ProcessTick flag = TICK_INDEPENDENT);
    void RemoveModule(IModule& module);

    int GetNumberOfModules();

    IModule* Lookup(const type_info& inf);

    void Start(IGameFactory* factory);
    void Stop();

};

} // NS Core
} // NS OpenEngine

#endif
