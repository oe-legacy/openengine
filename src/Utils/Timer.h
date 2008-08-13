// Platform independent timer.
//--------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_TIMER_H_
#define _OE_TIMER_H_

namespace OpenEngine {
namespace Utils {

/**
 * Platform independent timer.
 *
 * @class Timer Timer.h Utils/Timer.h
 */
class Timer {
private:
    //! start and stop time stamps.
    unsigned long start, stop;

public:

    Timer();

    void Start();
    void Stop();
    void Reset();

    unsigned long GetElapsedTime() const;
    unsigned long GetElapsedTimeAndReset();

    unsigned int GetElapsedIntervals(const unsigned int) const;
    unsigned int GetElapsedIntervalsAndReset(const unsigned int);

    bool IsRunning() const;

    static unsigned long GetTime();

};

} //NS Utils
} //NS OpenEngine

#endif // _OE_TIMER_H_
