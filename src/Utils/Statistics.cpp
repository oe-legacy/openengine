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

    Statistics::Statistics(float interval)
        : interval(interval),
          elapsed(0),
          frames(0) {}

    bool Statistics::IsTypeOf(const std::type_info& inf) { 
        return typeid(Statistics) == inf;
    }

    void Statistics::Initialize() {
        
    }

    void Statistics::Process(const float deltaTime, const float percent) {
        elapsed += deltaTime;
        frames += 1;
        if (elapsed > interval) {
            logger.info << "FPS: " << frames * 1000 / elapsed << logger.end;
            elapsed = 0;
            frames = 0;
        }
    }

    void Statistics::Deinitialize() {

    }

} // NS Utils
} // NS OpenEngine
