// Blending node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BLENDING_NODE_H_
#define _BLENDING_NODE_H_

#include <Scene/SceneNode.h>
#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>

#include <Scene/ISceneNodeVisitor.h>
#include <Renderers/IRenderer.h>
#include <Math/Vector.h>

// forward declarations
namespace OpenEngine {
namespace Scene {

using namespace OpenEngine::Scene;
using namespace OpenEngine::Math;

/**
 * Blending node.
 * 
 * 
 * @class BlendingNode BlendingNode.h Scene/BlendingNode.h
 */
class BlendingNode : public SceneNode {
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
    
    //! Accept of visitors
    void Accept(ISceneNodeVisitor& v);

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
        ar & boost::serialization::base_object<SceneNode>(*this);
        ar & source;
        ar & destination;
        ar & equation;
    }
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::BlendingNode)

#endif // _BLENDING_NODE_H_
