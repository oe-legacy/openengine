// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATED_TRANSFORMATION_NODE_H_
#define _ANIMATED_TRANSFORMATION_NODE_H_ 

#include <Scene/ISceneNode.h>

namespace OpenEngine {
namespace Scene {

    using namespace OpenEngine::Animation;

    
    class AnimatedTransformationNode : public Scene::ISceneNode {
        OE_SCENE_NODE(AnimatedTransformationNode, ISceneNode)

    public:
        AnimatedTransformationNode();
        AnimatedTransformationNode(const AnimatedTransformationNode& animTrans);
        virtual ~AnimatedTransformationNode();

        void SetAnimatedTransformation(AnimatedTransformation* animTrans);
        AnimatedTransformation* GetAnimatedTransformation();

    private:
        AnimatedTransformation* animTrans;
    };


} // NS Scene
} // NS OpenEngine

#endif
