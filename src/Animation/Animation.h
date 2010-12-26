// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <vector>

namespace OpenEngine {
    namespace Animations {
        class AnimatedTransformation;
    }
}

namespace OpenEngine {
namespace Animations {

    /**
     * An Animation represents an animation sequence eg. the walking cycle
     * of the character. An animation has a duration and a set of
     * animated transformations. Each animated transformation
     * describes the actual change in translation, 
     * rotation and scaling of a transformation node over time.   
     */
    class Animation {
    public:
        Animation();
        virtual ~Animation();

        void SetDuration(double timeInTicks);
        double GetDuration();

        void SetTicksPerSecond(double ticks);
        double GetTicksPerSecond();

        void SetName(std::string name);
        std::string GetName();

        unsigned int GetNumAnimatedTransformations();
        void AddAnimatedTransformation(AnimatedTransformation* anim);

        void UpdateTransformations(unsigned int time);

    private:
        std::string name;
        double duration; // In ticks.
        double ticksPerSecond;
        unsigned int numAnimTrans;
        std::vector<AnimatedTransformation*> animTrans;

    };
    
} // NS Animations
} // NS OpenEngine

#endif
