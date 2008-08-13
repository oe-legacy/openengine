// Platform independent timer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/Timer.h>

#include <Core/Exceptions.h>
#include <stdio.h>

#if defined(_WIN32)
    #include <Windows.h>
    #include <winbase.h>
    #include <time.h>
#else
    #include <sys/time.h>
#endif

namespace OpenEngine {
namespace Utils {

using OpenEngine::Core::Exception;

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
    if (!stop) return;
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
    if (!stop) stop = GetTime();
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
    if (stop) stop = start;
}

/**
 * Get the elapsed time.
 * If running the elapsed time is the deference between the call to \a
 * Start() and now. If not running it is the deference between the
 * call to Start() and Stop().
 *
 * @return Elapsed time in milliseconds
 */
unsigned long Timer::GetElapsedTime() const {
    // if paused we just return the time passed at the time of pausing
    return (stop ? stop : GetTime()) - start;
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
 * @return Elapsed time in milliseconds
 */
unsigned long Timer::GetElapsedTimeAndReset() {
    unsigned long now, elapsed;
    now = stop ? stop : GetTime();
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
 * @param interval Interval in milliseconds
 * @return Number of \a interval occurrences
 */
unsigned int Timer::GetElapsedIntervals(unsigned int interval) const {
    return GetElapsedTime() / interval;
}

/**
 * Get the number of elapsed time intervals and reset to the "rest" time.
 * Same as \a GetElapsedIntervals() but will reset the timer and keep
 * the rest product that is not included in the intervals. This is
 * useful for keeping track of frame occurrences for components that
 * need a fixed execution schedule.
 *
 * @param interval Interval in milliseconds
 * @return Number of \a interval occurrences
 */
unsigned int Timer::GetElapsedIntervalsAndReset(unsigned int interval) {
    unsigned long now, time;
    unsigned int times;
    now   = stop ? stop : GetTime();
    times = (now - start) / interval;
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
    return stop == 0;
}

/**
 * Get the system time in milliseconds.
 * The definition of what the "current time" is depends on the running
 * system.
 *
 * @todo We need to find some timing methods that are more stable over
 * for cpu scaling and system clocks. For unix type systems we may
 * wish to use times() together with sysconf to get the ticks per
 * second. On windows we might want to look at timeGetTime,
 * timeBeginPeriod and timeEndPeriod. 
 *
 * @return Time in milliseconds
 */
unsigned long Timer::GetTime() {
#if defined(_WIN32)
    LARGE_INTEGER ticksPerSecond, tick;
    if (!QueryPerformanceFrequency(&ticksPerSecond))
        throw Exception("no go QueryPerformance not present");
    if (!QueryPerformanceCounter(&tick))
        throw Exception("no go counter not installed");  
    return ((double)tick.QuadPart/(double)ticksPerSecond.QuadPart)*1000.0;
#else
    struct timeval t;
    gettimeofday( &t, NULL );
    return ( t.tv_sec * 1000.0 + t.tv_usec / 1000.0 );
#endif
}

} //NS Utils
} //NS OpenEngine
