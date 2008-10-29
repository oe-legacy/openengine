// Spot light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SPOT_LIGHT_NODE_H_
#define _OE_SPOT_LIGHT_NODE_H_

#include <Scene/LightNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Spot Light tree node.
 * 
 * @class SpotLightNode SpotLightNode.h Scene/SpotLightNode.h
 */
class SpotLightNode : public LightNode {
    OE_SCENE_NODE(SpotLightNode, LightNode)

public:
    float constAtt, linearAtt, quadAtt, cutoff, exponent;

    SpotLightNode();
    virtual ~SpotLightNode();

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

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::SpotLightNode)

#endif // _SPOT_LIGHT_NODE_H_
