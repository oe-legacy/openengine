// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATION_NODE_H_
#define _ANIMATION_NODE_H_

#include <Scene/ISceneNode.h>
#include <Animation/Animation.h>

namespace OpenEngine {
namespace Scene {

    using OpenEngine::Animations::Animation;
    
    class AnimationNode : public Scene::ISceneNode {
        OE_SCENE_NODE(AnimationNode, ISceneNode)

    public:
        AnimationNode();
        AnimationNode(Animation* animation);
        virtual ~AnimationNode();

        Animation* GetAnimation();
        void SetAnimation(Animation* animation);

        const std::string ToString() const;

    private:
        Animation* animation;
    };


} // NS Scene
} // NS OpenEngine

#endif
