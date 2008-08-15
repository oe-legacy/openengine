// Engine events.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_ENGINE_EVENTS_H_
#define _OE_ENGINE_EVENTS_H_

#include <Utils/Timer.h>

namespace OpenEngine {
namespace Core {

using OpenEngine::Utils::Time;

/**
 * Engine initialization event argument.
 */
struct InitializeEventArg { };

/**
 * Engine deinitialization event argument.
 */
struct DeinitializeEventArg { };

/**
 * Engine process event argument.
 */
struct ProcessEventArg {
    Time start;                 //!< time of engine loop start.
    unsigned int approx;        //!< approximate engine loop time.
    ProcessEventArg(Time start, unsigned long approx)
        : start(start), approx(approx) {}
};

} // NS Core
} // NS OpenEngine

#endif // _OE_ENGINE_EVENTS_H_
