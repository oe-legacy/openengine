// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "AnimatedTransformation.h"
#include <utility>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {


AnimatedTransformation::AnimatedTransformation(TransformationNode* target) {
    this->target = target;
}

AnimatedTransformation::~AnimatedTransformation() {
}

void AnimatedTransformation::SetName(std::string name) {
    this->name = name;
}

std::string AnimatedTransformation::GetName() {
    return name;
}
        
void AnimatedTransformation::SetAnimatedNode(TransformationNode* target) {
    this->target = target;
}

TransformationNode* AnimatedTransformation::GetAnimatedNode() {
    return target;
}
        
void AnimatedTransformation::AddRotationKey(unsigned int time, Math::Quaternion<float> key) {
    rotationKeys.push_back(std::make_pair(time, key));
}

void AnimatedTransformation::UpdateAndApply(unsigned int time) {
    std::pair<double, Math::Quaternion<float> > elm, kStart, kEnd;

    std::vector< std::pair<double, Math::Quaternion<float> > >::iterator itr;
    for(itr=rotationKeys.begin(); itr!=rotationKeys.end(); itr++){
        elm = *itr;
        if( time >= elm.first ) {
            kStart = elm;
        }else{
            kEnd = elm;
            break;
        }
    }

    // TODO: interpolation between kStart.second and kEnd.second.
    //    logger.info << "Using  : " << kStart.first << logger.end;

    // Apply rotation to affected transformation node.
    target->SetRotation(kStart.second);
}


} // NS Animations
} // NS OpenEngine
