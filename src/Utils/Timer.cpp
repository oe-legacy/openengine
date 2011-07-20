// Platform independent timer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/Timer.h>

#include <Meta/Time.h>
#include <Core/Exceptions.h>
#include <Utils/Convert.h>

#include <cstring>
#include <stdio.h>
#include <limits.h>
#include <iomanip>
/*
#if defined(_WIN32)
    #include <Windows.h>
    #include <winbase.h>
#endif
*/
namespace OpenEngine {
namespace Utils {

using OpenEngine::Core::Exception;
using OpenEngine::Utils::Convert;

static const unsigned int second = 1000000;

Time::Time() : sec(0), usec(0) {}
Time::Time(const uint32_t usec) : sec(usec / second), usec(usec % second) {}
Time::Time(const uint64_t sec, const uint32_t usec) : sec(sec), usec(usec) {}

void Time::operator+=(const Time t) {
    sec  += t.sec;
    usec += t.usec;
    if (usec >= second) {
        sec++;
        usec -= second;
    }
}

void Time::operator-=(const Time t) {
#if OE_SAFE
    if (sec < t.sec || (sec <= t.sec && usec < t.usec))
        throw Exception("Attempt to subtract a future time from a past time.");
#endif
    sec  -= t.sec;
    if (t.usec > usec) {
        sec--;
        usec += second - t.usec;
    } else {
        usec -= t.usec;
    }
}

const Time Time::operator+(const Time t) const {
    Time s(*this);
    s += t;
    return s;
}

const Time Time::operator-(const Time t) const {
    Time s(*this);
    s -= t;
    return s;
}

const Time Time::operator=(const unsigned int i) {
    sec = i / second; usec = i % second;
    return *this;
}

bool Time::operator<(const Time t) const {
    if (sec < t.sec)
        return true;
    else if (sec == t.sec)
        return usec < t.usec;
    return false;
}

bool Time::operator>(const Time t) const {
    return t < *this;
}

bool Time::operator==(const Time t) const {
    return ((sec == t.sec) && (usec == t.usec));
}

bool Time::operator!=(const Time t) const {
    return ((sec != t.sec) || (usec != t.usec));
}

bool Time::operator<=(const Time t) const {
    return ((*this < t) || (*this == t));
}

bool Time::operator>=(const Time t) const {
    return ((*this > t) || (*this == t));
}

/**
 * String representation.
 * Ex. <10 sec, 500000 microsec>
 *
 * @return Time as string
 */
std::string Time::ToString() const {
    std::ostringstream out;
    out << "<" << sec << " sec, ";
    out << std::setw(6) << std::setfill('0');
    out << usec << " microsec>";
    return out.str();
}
    
bool Time::IsZero() const {
    return sec == 0 && usec == 0;
}

bool Time::IsNonZero() const {
    return !IsZero();
}

unsigned int Time::AsInt() const {
#if OE_SAFE
    if (sec > UINT_MAX / second - 1)
        throw Exception("Overflow when converting Time("+
                        Convert::ToString<uint64_t>(sec)+", "+
                        Convert::ToString<uint32_t>(usec)+") to unsigned int.");
#endif
    return sec * second + usec;
}

uint32_t Time::AsInt32() const {
#if OE_SAFE
    // @todo UINT32_MAX is undefined but is in stdint.h ??
    // if (sec > UINT32_MAX / 1000000 - 1)
    //     throw Exception("Overflow when converting Time("+
    //                     Convert::ToString<uint64_t>(sec)+", "+
    //                     Convert::ToString<uint32_t>(usec)+") to int.");
#endif
    return sec * second + usec;
}

uint64_t Time::AsInt64() const {
#if OE_SAFE
    // @todo UINT64_MAX is undefined but is in stdint.h ??
    // if (sec > UINT64_MAX / 1000000 - 1)
    //     throw Exception("Overflow when converting Time("+
    //                     Convert::ToString<uint64_t>(sec)+", "+
    //                     Convert::ToString<uint32_t>(usec)+") to an unsigned int.");
#endif
    return sec * second + usec;
}

/**
 * Stream operator to ease the use of ToString method.
 */
std::ostream& operator<<(std::ostream& os, const Time e) {
    os<<e.ToString();
    return os;
}

/**
 * Construct a time object.
 * The timer is not running initially, i.e. in stopped state.
 */
Timer::Timer()
    : start(1),
      stop(1) {
    // this is ok as the delta time is equal to zero (stop - start)
}

/**
 * Start the timer.
 * If the timer is already running calls to \a Start() are ignored.
 * If not running the timer will be resumed from the current elapsed time.
 */
void Timer::Start() {
    // increment the start time with the time passed since we stopped
    if (stop.IsZero()) return;
    start += GetTime() - stop;
    stop = 0;
}

/**
 * Stop the timer.
 * If the timer is not running calls to \a Stop() are ignored.
 * If it is running the timer will be paused.
 */
void Timer::Stop() {
    // set the stop time only if we are not stopped already
    if (stop.IsZero()) stop = GetTime();
}

/**
 * Reset the timer.
 * If the timer is running it will be reset on the fly and continue to
 * time after the call to \a Reset(). If not running the timer is
 * reset to an elapsed time of zero, semantically equivalent to a
 * freshly created timer.
 */
void Timer::Reset() {
    // always set new start time and if we are stopped remain so but
    // update the stop time to now.
    start = GetTime();
    if (stop.IsNonZero()) stop = start;
}

/**
 * Get the elapsed time.
 * If running the elapsed time is the deference between the call to \a
 * Start() and now. If not running it is the deference between the
 * call to Start() and Stop().
 *
 * @return Elapsed time in microseconds
 */
Time Timer::GetElapsedTime() const {
    // if paused we just return the time passed at the time of pausing
    return (stop.IsNonZero() ? stop : GetTime()) - start;
}

/**
 * Get the elapsed time and reset the timer.
 * Same as executing
 * @code
 * timer->GetElapsedTime(); timer->Reset()
 * @endcode
 * but may omit unnecessary calls to \a GetTime().
 * Does not change the running state of the timer.
 *
 * @return Elapsed time in microseconds
 */
Time Timer::GetElapsedTimeAndReset() {
    Time now, elapsed;
    now = stop.IsNonZero() ? stop : GetTime();
    elapsed = now - start;
    start = now;
    return elapsed;
}

/**
 * Get the number of time intervals that have elapsed.
 * The number is the amount of complete occurrences, i.e. rounded
 * down. If the value of "elapsed time" is described in \a
 * GetElapsedTime().
 *
 * @see GetElapsedTime
 * @param interval Interval in microseconds
 * @return Number of \a interval occurrences
 */
unsigned int Timer::GetElapsedIntervals(unsigned int interval) const {
    return GetElapsedTime().AsInt64() / interval;
}

/**
 * Get the number of elapsed time intervals and reset to the "rest" time.
 * Same as \a GetElapsedIntervals() but will reset the timer and keep
 * the rest product that is not included in the intervals. This is
 * useful for keeping track of frame occurrences for components that
 * need a fixed execution schedule.
 *
 * @param interval Interval in microseconds
 * @return Number of \a interval occurrences
 */
unsigned int Timer::GetElapsedIntervalsAndReset(unsigned int interval) {
    Time now, time;
    unsigned int times;
    now   = stop.IsNonZero() ? stop : GetTime();
    times = (now - start).AsInt() / interval;
    time  = times * interval;
    start += time;
    return times;
}

/**
 * Check if the timer is currently timing.
 *
 * @return True if running
 */
bool Timer::IsRunning() const {
    return stop.IsZero();
}

/**
 * Get the system time.
 * The definition of what the "current time" is depends on the running
 * system. On most systems it is the time since the UNIX epoch.
 *
 * @todo We need to check that these timing methods are stable wrt.
 * to cpu scaling and system clocks. For unix type systems we may
 * wish to use times() together with sysconf to get the ticks per
 * second. On windows we might want to look at timeGetTime,
 * timeBeginPeriod and timeEndPeriod.
 *
 * Windows implementation from:
 * http://www.openasthra.com/c-tidbits/gettimeofday-function-for-windows/
 *
 * @return Current time.
 */
Time Timer::GetTime() {
    /*
#if defined(_WIN32)
    #if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
        #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
    #else
        #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
    #endif
    Time tv;
    FILETIME ft;
    unsigned __int64 res = 0;
    GetSystemTimeAsFileTime(&ft);
    res |= ft.dwHighDateTime;
    res <<= 32;
    res |= ft.dwLowDateTime;
    // converting file time to unix epoch
    res /= 10;
    res -= DELTA_EPOCH_IN_MICROSECS; 
    return Time(res / 1000000UL, res % 1000000UL);
#else
*/
    struct timeval t;
    gettimeofday( &t, NULL );
    return Time(t.tv_sec, t.tv_usec);
//#endif
}

} //NS Utils
} //NS OpenEngine
