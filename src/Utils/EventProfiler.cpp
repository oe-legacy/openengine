// Event profiling utility. 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/EventProfiler.h>
#include <Logging/Logger.h>
#include <string>
#include <math.h>

namespace OpenEngine {
namespace Utils {

using Logging::Logger;

EventProfiler::EventProfiler()  {
    timer.Start();
}

void EventProfiler::DumpInfo() {
    std::list<Intercepter*>::iterator i, h;
    unsigned int c, m;
    m = (int)(log(timer.GetElapsedTime().AsInt())/log(10)) + 1;
    h = is.begin();
    
    logger.info << "Event profiling info:" << logger.end
                << "\tTime";
    c = m - 4; for (;c>0;c--) logger.info << " ";
    logger.info <<"  Calls   Name" << logger.end
                << "\t" << timer.GetElapsedTime().AsInt() << "      \tTotal Time"
                << logger.end;
    
    while (is.size() > 0) {
        // find the largest guy
        for (i=is.begin(); i!=is.end(); i++) {
            if ((*i)->timer.GetElapsedTime().AsInt() >
                (*h)->timer.GetElapsedTime().AsInt())
                h = i;
        }
        logger.info << "\t";
        // compute the space padding
        c = m - ((int)(log((*h)->timer.GetElapsedTime().AsInt())/log(10)) + 1);
        for (;c>0;c--) logger.info << " ";
        logger.info << (*h)->timer.GetElapsedTime().AsInt() << "  "
                    << (*h)->count << " \t"
                    << (*h)->name
                    << logger.end;
        // remove the largest guy and continue
        is.erase(h);
        h = is.begin();
    }
}

} // NS Utils
} // NS OpenEngine
