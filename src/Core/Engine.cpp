// Engine implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/Engine.h>
#include <Logging/Logger.h>
#include <Utils/Timer.h>

namespace OpenEngine {
namespace Core {

using OpenEngine::Utils::Time;
using OpenEngine::Utils::Timer;

/**
 * Engine constructor.
 */
Engine::Engine() : running(false) {

}

/**
 * Main engine loop.
 */
void Engine::StartMainLoop() {
    Time time, _time;
    unsigned int approx;
    const unsigned int count = 10;
    unsigned int index = 0;
    unsigned int loops[count];

    // we initialize the approximate frame time to 50 milliseconds
    for (unsigned int i=0; i<count; i++) loops[i] = 50;

    // set the initial time
    time = Timer::GetTime();

    // run the engine loop
    running = true;
    while (running) {

        // calculate the approximate frame time
        // Note: we assume that the sum of the loops do not overflow
        // fps of 20 => (frame ~= 50 msec = 50.000 usec) x 10 = 500.000
        approx = 0;
        for (unsigned int i=0; i<count; i++)
            approx += loops[i];
        approx = approx / count;

        // process listeners
        process.Notify(ProcessEventArg(time, approx));

        // save frame time to perform the next approximation
        _time = Timer::GetTime();
        loops[index] = (_time - time).AsInt();
        time = _time;

        // update the loop index
        index = (index + 1) % count;
    }
}

/**
 * @see IEngine::Start()
 */
void Engine::Start() {
    if (running) {
        logger.warning << "Ignoring start request - engine already running." << logger.end;
        return;
    }
    initialize.Notify(InitializeEventArg());
    StartMainLoop();
    deinitialize.Notify(DeinitializeEventArg());
}

/**
 * @see IEngine::Stop()
 */
void Engine::Stop() {
    running = false;
}

/**
 * @see IEngine::InitializeEvent()
 */
IEvent<InitializeEventArg>& Engine::InitializeEvent() {
    return initialize;
}

/**
 * @see IEngine::ProcessEvent()
 */
IEvent<ProcessEventArg>& Engine::ProcessEvent() {
    return process;
}

/**
 * @see IEngine::DeinitializeEvent()
 */
IEvent<DeinitializeEventArg>& Engine::DeinitializeEvent() {
    return deinitialize;
}

} // NS Core
} // NS OpenEngine
