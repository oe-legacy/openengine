// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _ANIMATED_TRANSFORMATION_H_
#define _ANIMATED_TRANSFORMATION_H_

#include <Math/Quaternion.h>
#include <vector>
#include <utility>
#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Animations {

    // Forward declaration
    using namespace OpenEngine::Scene;

    /**
     * An Animated transformation node represents the actual change of
     * a transformation node over time. It has a key frame to value
     * map for each channel. A channel represents the change in
     * position, rotation or scaling of a given transformation node.
     */

    class AnimatedTransformation {
    public:
        AnimatedTransformation(TransformationNode* target);
        virtual ~AnimatedTransformation();

        void SetName(std::string name);
        std::string GetName();
        
        void SetAnimatedNode(TransformationNode* trans);
        TransformationNode* GetAnimatedNode();
        
        void AddRotationKey(unsigned int time, Math::Quaternion<float> key);

        void UpdateAndApply(unsigned int time);

    private:
        std::string name;
        TransformationNode* target;
        // time/value keys for each channel
        std::vector< std::pair<double, Math::Quaternion<float> > > rotationKeys;
        std::vector< std::pair<double, Math::Vector<3,float> > >   positionKeys;
        std::vector< std::pair<double, Math::Vector<3,float> > >   scalingKeys;

    };

} // NS Animations
} // NS OpenEngine

#endif
