// Platform independent timer
//--------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TIMER_H_
#define _TIMER_H_

#include <string>

namespace OpenEngine {
namespace Utils {

using std::string;

/**
 * Platform independent timer.
 *
 * @class Timer Timer.h Utils/Timer.h
 */
class Timer {
public:
 
    /**
     * Get a time reference.
     * Is comparible to the GetTickCount() from the Windows API.
     *
     * @return Time count
     */
    static double GetTime();

    /**
     * Get a timestamp as string.
     *
     * @return string timestamp
     */
    static string GetDateTime();

};

} //NS Utils
} //NS OpenEngine

#endif
