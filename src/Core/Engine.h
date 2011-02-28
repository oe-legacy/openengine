// Engine implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_ENGINE_H_
#define _OE_ENGINE_H_

#include <Core/IEngine.h>
#include <Core/IEvent.h>
#include <Core/Event.h>

namespace OpenEngine {
namespace Core {

class Engine : public IEngine {
private:
    bool running;
    Event<InitializeEventArg>   initialize;
    Event<ProcessEventArg>      process;
    Event<DeinitializeEventArg> deinitialize;
public:
    Engine();
    virtual void Start();
    virtual void Stop();
    void StartMainLoop();
    virtual IEvent<InitializeEventArg>&   InitializeEvent();
    virtual IEvent<ProcessEventArg>&      ProcessEvent();
    virtual IEvent<DeinitializeEventArg>& DeinitializeEvent();
};

} // NS Core
} // NS OpenEngine

#endif // NS _OE_ENGINE_H_
