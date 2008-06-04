// Spot light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SPOT_LIGHT_NODE_H_
#define _SPOT_LIGHT_NODE_H_

#include <Scene/LightNode.h>
#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>

#include <Math/Vector.h>

// forward declarations
namespace OpenEngine {
namespace Scene {

using namespace OpenEngine::Scene;
using namespace OpenEngine::Math;

/**
 * Spot Light tree node.
 * 
 * 
 * @class SpotLightNode SpotLightNode.h Scene/SpotLightNode.h
 */
class SpotLightNode : public LightNode {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<LightNode>(*this);
        ar & constAtt;
        ar & linearAtt;
        ar & quadAtt;
        ar & cutoff;
        ar & exponent;
   }

public:
    SpotLightNode();
    virtual ~SpotLightNode();
    float constAtt, linearAtt, quadAtt, cutoff, exponent;

    //! Accept of visitors
    void Accept(ISceneNodeVisitor& v);
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::SpotLightNode)

#endif // _SPOT_LIGHT_NODE_H_
