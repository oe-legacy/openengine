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

#include <Meta/Types.h>
#include <string>

namespace OpenEngine {
namespace Utils {

/**
 * Time data type.
 * Provides an interface to a time structure similar to that obtained
 * by \a gettimeofday.
 *
 * @todo We should look at how we can abstract Time and Timer to allow
 * alternative representation of ``time'', such as vector clocks.
 *
 * @class Time Time.h Utils/Timer.h
 */
class Time {
    friend class Timer; // allow Timer to use operator=
private:
    /** @todo: should this be removed, it causes things like 
        Time dt = 1000.0; to parse be the compiler without warnings */
    const Time operator=(const unsigned int i);
public:
    uint64_t sec;
    uint32_t usec;
    explicit Time();
    explicit Time(const uint32_t usec);
    Time(const uint64_t sec, const uint32_t usec);
    void operator+=(const Time t);
    void operator-=(const Time t);
    const Time operator+(const Time t) const;
    const Time operator-(const Time t) const;
    const bool operator<(const Time t) const;
    const bool operator>(const Time t) const;
    const bool operator==(const Time t) const;
    const bool operator!=(const Time t) const;
    const bool operator<=(const Time t) const;
    const bool operator>=(const Time t) const;
    const bool IsZero() const;
    const bool IsNonZero() const;
    const unsigned int AsInt() const;
    const uint32_t AsInt32() const;
    const uint64_t AsInt64() const;
    const std::string ToString() const;
};

std::ostream& operator<<(std::ostream& os, const Time e);

/**
 * Platform independent timer.
 *
 * @class Timer Timer.h Utils/Timer.h
 */
class Timer {
private:
    //! start and stop time stamps.
    Time start, stop;

public:

    Timer();

    void Start();
    void Stop();
    void Reset();

    Time GetElapsedTime() const;
    Time GetElapsedTimeAndReset();

    unsigned int GetElapsedIntervals(const unsigned int) const;
    unsigned int GetElapsedIntervalsAndReset(const unsigned int);

    bool IsRunning() const;

    static Time GetTime();

};

} //NS Utils
} //NS OpenEngine

#endif // _OE_TIMER_H_
