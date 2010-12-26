// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <Core/IModule.h>
#include <vector>

namespace OpenEngine { 
    namespace Utils {
        class Timer;
    }
    namespace Animations {
        class Animation;
    }
    namespace Scene { 
        class AnimationNode; 
    } 
}

namespace OpenEngine {
namespace Animations {

    using OpenEngine::Core::IModule;
    using OpenEngine::Scene::AnimationNode;
    using OpenEngine::Utils::Timer;

    class Animator : public IModule {
    public:
        Animator(AnimationNode* animNode);
        virtual ~Animator();

        unsigned int GetNumAnimations();
        Animation* GetAnimation(unsigned int idx);
                
        void Animate(unsigned int idx);

        // Engine call backs.
        void Handle(Core::InitializeEventArg arg);
        void Handle(Core::ProcessEventArg arg);
        void Handle(Core::DeinitializeEventArg arg);

    private:
        AnimationNode* animRoot;
        std::vector<AnimationNode*> animList;
        Animation* curAnim;
        Timer timer;
    
        void UpdateAnimation();
    };
    

} // NS Animation
} // NS OpenEngine

#endif
