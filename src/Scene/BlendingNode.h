// Blending node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_BLENDING_NODE_H_
#define _OE_BLENDING_NODE_H_

#include <Scene/ISceneNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Blending node.
 * 
 * @class BlendingNode BlendingNode.h Scene/BlendingNode.h
 */
class BlendingNode : public ISceneNode {
    OE_SCENE_NODE(BlendingNode, ISceneNode)

public:
    enum BlendingFactor {
        ZERO, ONE,
        SRC_COLOR, ONE_MINUS_SRC_COLOR,
        DST_COLOR, ONE_MINUS_DST_COLOR,
        SRC_ALPHA, ONE_MINUS_SRC_ALPHA,
        DST_ALPHA, ONE_MINUS_DST_ALPHA
        //@todo: color - see redbook 234 for the rest.
    };
    
    enum BlendingEquation { ADD, SUBTRACT, REVERSE_SUBTRACT, MIN, MAX };
    
    BlendingNode();
    virtual ~BlendingNode() {}

    BlendingFactor GetSource();
    void SetSource(BlendingFactor source);
    BlendingFactor GetDestination();
    void SetDestination(BlendingFactor destination);
    BlendingEquation GetEquation();
    void SetEquation(BlendingEquation equation);

private: 
    BlendingFactor source;
    BlendingFactor destination;
    BlendingEquation equation;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & source;
        ar & destination;
        ar & equation;
    }
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::BlendingNode)

#endif // _OE_BLENDING_NODE_H_
