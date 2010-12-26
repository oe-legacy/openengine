// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include "AnimatedTransformationNode.h"
#include <Scene/TransformationNode.h>


namespace OpenEngine {
namespace Scene {


AnimatedTransformationNode::AnimatedTransformationNode() : animated(NULL) {
}

AnimatedTransformationNode::AnimatedTransformationNode(const AnimatedTransformationNode& animTrans) {
}

AnimatedTransformationNode::~AnimatedTransformationNode() {
}

void AnimatedTransformationNode::SetAnimatedTransformation(AnimatedTransformation* animTrans) {
    this->animTrans = animTrans;
}

AnimatedTransformation* AnimatedTransformationNode::GetAnimatedTransformation() {
    return animTrans;
}

} // NS Scene
} // NS OpenEngine
