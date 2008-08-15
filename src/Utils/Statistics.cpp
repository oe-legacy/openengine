// Statistics module.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/Statistics.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Logging;

Statistics::Statistics(unsigned int interval)
    : interval(interval)
    , frames(0) {
    timer.Start();
}

void Statistics::Handle(ProcessEventArg arg) {
    frames += 1;
    unsigned long elapsed = timer.GetElapsedTime();
    if (elapsed > interval) {
        logger.info << "FPS: " << (double)frames * 1000 / (double)elapsed << logger.end;
        frames = 0;
        timer.Reset();
    }
}

} // NS Utils
} // NS OpenEngine
