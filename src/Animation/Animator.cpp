// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "Animator.h"
#include <Logging/Logger.h>
#include <Scene/SearchTool.h>
#include <Scene/AnimationNode.h>
#include <Animation/Animation.h>
#include <list>

namespace OpenEngine {
namespace Animations {

using OpenEngine::Logging::Logger;
using OpenEngine::Animations::Animation;
using namespace OpenEngine::Scene;

Animator::Animator(AnimationNode* animNode) : animRoot(animNode), curAnim(NULL) {
    // Search the animation tree for sequences
    SearchTool search;
    std::list<AnimationNode*> res;
    res = search.DescendantAnimationNodes((ISceneNode*)animNode);
    // Throw results in vector list for convenience.
    std::list<AnimationNode*>::iterator itr;
    for(itr=res.begin(); itr!=res.end(); itr++){
        animList.push_back(*itr);
    }
}

Animator::~Animator() {
}
    
unsigned int Animator::GetNumAnimations() {
    return animList.size();
}

Animation* Animator::GetAnimation(unsigned int idx) {
    if( idx < animList.size() )
        return animList[idx]->GetAnimation();
    else
        return NULL;
}
           
void Animator::Animate(unsigned int idx) {
    if( idx < animList.size() ){
        if( (curAnim = animList[idx]->GetAnimation()) != NULL ){
            logger.info << "Active Animation: " << curAnim->GetName() << " with duration " << curAnim->GetDuration() << logger.end;
            logger.info << "Active Animation num animated transformations: " << curAnim->GetNumAnimatedTransformations() << logger.end;
            timer.Start();
        }else{
            logger.warning << "Animation invalid, " << curAnim->GetName() << " sequence num " << idx << logger.end;
        }
    }
    else{
        logger.warning << "Animation out of range, " << curAnim->GetName() << " sequence num " << idx << logger.end;
    }
}

void Animator::Handle(Core::InitializeEventArg arg) {
    logger.info << "init" << logger.end;
}

void Animator::Handle(Core::ProcessEventArg arg) {
    if( curAnim ) {
        UpdateAnimation();
        //   logger.info << "process with time: " << timer.GetElapsedTime() << logger.end;
    
    }
}

void Animator::Handle(Core::DeinitializeEventArg arg) {
    logger.info << "deinit" << logger.end;
}

void Animator::UpdateAnimation() {
    // Check time limits.
    if( timer.GetElapsedTime().usec > curAnim->GetDuration() ){
        //logger.info << "resetting animation time" << logger.end;
        timer.Reset();
    }
    //    logger.info << "Current: " << timer.GetElapsedTime().usec << logger.end;

    curAnim->UpdateTransformations(timer.GetElapsedTime().usec);
}

} // NS Animation
} // NS OpenEngine
