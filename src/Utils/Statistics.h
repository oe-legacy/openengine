// Statistics module.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Utils/Timer.h>

namespace OpenEngine {
namespace Utils {

using OpenEngine::Core::IListener;
using OpenEngine::Core::ProcessEventArg;

/**
 * Statistics module.
 * Collects statistical information and prints them to the logger info
 * stream at a given interval.
 *
 * @class Statistics Statistics.h Utils/Statistics.h
 */
class Statistics : public IListener<ProcessEventArg> {
private:
    Timer timer;
    unsigned int interval;
    int frames;

public:

    /**
     * Create a statistics module.
     *
     * @param interval Interval of when to print statistic info.
     */
    Statistics(const unsigned int interval);
    void Handle(ProcessEventArg arg);

};

} // NS Utils
} // NS OpenEngine

#endif // _STATISTICS_H_
