// Engine interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_ENGINE_INTERFACE_H_
#define _OE_ENGINE_INTERFACE_H_

#include <Core/IEvent.h>
#include <Core/EngineEvents.h>

namespace OpenEngine {
namespace Core {

/**
 * Engine Interface.
 * The engine acts as the main processor. The engine notifies
 * initialization, process and deinitialization signals for engine
 * components to react upon. The process is the perfered way to
 * receive processing time.
 *
 * @class IEngine IEngine.h Core/IEngine.h
 */
class IEngine {
public:

    /**
     * Remove the engine instance on destruction.
     */
    virtual ~IEngine() {};

    /**
     * Start the engine.
     */
    virtual void Start() = 0;

    /**
     * Shutdown the engine. When \a Stop is called the engine loop
     * will stop after the current loop completes and will trigger the
     * deinitialization event.
     */
    virtual void Stop() = 0;

    /**
     * Event triggered on engine initialization.
     */
    virtual IEvent<InitializeEventArg>& InitializeEvent() = 0;

    /**
     * Event triggered for each engine loop.
     */
    virtual IEvent<ProcessEventArg>& ProcessEvent() = 0;

    /**
     * Event triggered on engine deinitialization.
     */
    virtual IEvent<DeinitializeEventArg>& DeinitializeEvent() = 0;

};

} // NS Core
} // NS OpenEngine

#endif // _OE_ENGINE_INTERFACE_H_
