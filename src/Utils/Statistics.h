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

#include <Core/IModule.h>

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Core;

/**
 * Statistics module.
 * Collects statistical information and prints them to the logger info
 * stream at a given interval.
 *
 * @class Statistics Statistics.h Utils/Statistics.h
 */
class Statistics : public IModule {
private:
    float interval, elapsed;
    int frames;
    
public:

    /**
     * Create a statistics module.
     *
     * @param interval Interval of when to print statistic info.
     */
    Statistics(const float interval);

    // IModule methods
    bool IsTypeOf(const std::type_info& inf);
    void Initialize();
    void Process(const float deltaTime, const float percent);
    void Deinitialize();

};

} // NS Utils
} // NS OpenEngine

#endif // _STATISTICS_H_
