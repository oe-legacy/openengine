// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/TickEngine.h>
#include <Logging/Logger.h>
#include <Utils/Timer.h>
#include <cstdlib>

namespace OpenEngine {
namespace Core {

using OpenEngine::Utils::Time;
using OpenEngine::Utils::Timer;



TickEngine::TickEngine() {
    
}

void TickEngine::Tick() {
    
    Time _time;

    unsigned int approx = 0;
    for (int i=0;i<10;i++) 
        approx += loops[i];
    approx = approx / 10;

    process.Notify(ProcessEventArg(time,approx));
    
    _time = Timer::GetTime();
    loops[index] = (_time - time).AsInt();
    time = _time;

    index = (index + 1) % 10;
    
}

void TickEngine::Start() {
    initialize.Notify(InitializeEventArg());

           
    // Ready the approx calculation
    index = 0;
    for (int i=0;i<10;i++) 
        loops[i] = 50;

    time = Timer::GetTime();
    
}

void TickEngine::Stop() {
    // only way to end the glutMainLoop
    deinitialize.Notify(DeinitializeEventArg());

    exit(0);
}


/**
 * @see IEngine::InitializeEvent()
 */
IEvent<InitializeEventArg>& TickEngine::InitializeEvent() {
    return initialize;
}

/**
 * @see IEngine::ProcessEvent()
 */
IEvent<ProcessEventArg>& TickEngine::ProcessEvent() {
    return process;
}

/**
 * @see IEngine::DeinitializeEvent()
 */
IEvent<DeinitializeEventArg>& TickEngine::DeinitializeEvent() {
    return deinitialize;
}


} // NS Core
} // NS OpenEngine
