// Platform independent timer
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
#endif

#if defined(linux)
    #include <sys/time.h>
#endif

namespace OpenEngine {
namespace Utils {

using OpenEngine::Core::Exception;

double Timer::GetTime() {
#if defined(_WIN32)
    LARGE_INTEGER ticksPerSecond, tick;
    if (!QueryPerformanceFrequency(&ticksPerSecond))
        throw Exception("no go QueryPerformance not present");
    if (!QueryPerformanceCounter(&tick))
        throw Exception("no go counter not installed");  
    return ((double)tick.QuadPart/(double)ticksPerSecond.QuadPart)*1000.0;
#endif

#if defined(linux) || defined(__APPLE__)
  struct timeval t;
  gettimeofday( &t, NULL );
  return ( t.tv_sec * 1000.0 + t.tv_usec / 1000.0 );
#endif  
}

std::string Timer::GetDateTime() {
    time_t t;
    time (&t);// get the current time

    char buf[20];
    memset (buf, '0', 20);// this terminates the string

	strftime (buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", localtime(&t));
    return std::string(buf);
}

} //NS Utils
} //NS OpenEngine
