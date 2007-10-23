// Game engine interface
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_GAME_ENGINE_H_
#define _INTERFACE_GAME_ENGINE_H_

#include <vector>
#include <Core/IModule.h>

namespace OpenEngine {
namespace Core {

using OpenEngine::Core::IModule;

// forward declarations
class IGameFactory;

/**
 * The Game Engine Interface.
 * The Game Engine acts as module container. The Game Engine is
 * responsible for performing module initialization and
 * deinitialization tasks. 
 * Follows the singelton pattern.
 *
 * @class IGameEngine IGameEngine.h Core/IGameEngine.h
 */
class IGameEngine {
protected:

    /**
     * Private constructor.
     *
     * @see Instance()
     */
    IGameEngine();

    //! The only existing instance.
    static IGameEngine* instance;

public:

    /**
     * Process module tick setting.
     *
     * @enum ProcessTick ..
     */
    enum ProcessTick {
        //! process independent of the tick time (on every engine loop).
        TICK_INDEPENDENT,
        //! process once every tick time.
        TICK_DEPENDENT
    };

    /**
     * Get game engine instance.
     *
     * @return Reference to GameEngine instance
     */
    static IGameEngine& Instance();

    /**
     * Remove the engine instance on destruction.
     */
    virtual ~IGameEngine();

    /**
     * Get the current tick time.
     *
     * @return Current tick time.
     */
    virtual float GetTickTime() = 0;

    /**
     * Set the tick time.
     * This affects the processing of all modules added with the
     * TICK_DEPENDENT option.
     *
     * @param time Process tick time.
     */
    virtual void SetTickTime(const float time) = 0;

    /**
     * Add module
     *
     * @param module Module to add.
     * @param flag Flag of the modules tick dependency.
     */
    virtual void AddModule(IModule& module, const ProcessTick flag = TICK_INDEPENDENT) = 0;

    /**
     * Remove module
     *
     * @param module to be removed
     */
    virtual void RemoveModule(IModule& module) = 0;

    /**
     * Lookup module of same type as search.
     * 
     * @param  inf Type info as returned by \a typeid(moduleclass)
     * @return pointer to \a IModule or \a NULL if module of type
     *         is not found. 
     */
    virtual IModule* Lookup(const std::type_info& inf) = 0;

    /**
     * Get number of loaded modules
     *
     * @return integer value
     */
    virtual int GetNumberOfModules() = 0;

    /**
     * Start the engine.
     *
     * The specified game factory is used to set up the engine modules
     * and other customization tasks.
     * The game engine is responsible for deleting the factory after
     * use.
     *
     * @see IGameFactory
     * @param factory Game factory
     */
    virtual void Start(IGameFactory* factory) = 0;

    /**
     * Shutdown engine. When Stop is called the engine loop
     * stops running and all modules gets deinitialized.
     */
    virtual void Stop() = 0;

};

} // NS Core
} // NS OpenEngine

#endif // _INTERFACE_GAME_ENGINE_H_
