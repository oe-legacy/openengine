// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "AnimationNode.h"
#include <Animation/Animation.h>
#include <string>

using namespace OpenEngine::Animations;
namespace OpenEngine {
namespace Scene {

AnimationNode::AnimationNode() : animation(NULL) {
}

AnimationNode::AnimationNode(Animation* animation) : animation(animation) {
}


AnimationNode::~AnimationNode() {
}


Animation* AnimationNode::GetAnimation() {
    return animation;
}

void AnimationNode::SetAnimation(Animation* animation) {
    this->animation = animation;
}


const std::string AnimationNode::ToString() const {
    std::string str;
    if( animation ){
        str = animation->GetName();
    }else{
        str = "null";
    }

    str.append("\n[AnimationNode]");
    return str;
}

} // NS Scene
} // NS OpenEngine
