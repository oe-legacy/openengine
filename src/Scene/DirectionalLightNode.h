// Light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_DIRECTIONAL_LIGHT_NODE_H_
#define _OE_DIRECTIONAL_LIGHT_NODE_H_

#include <Scene/LightNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Directional Light tree node.
 * 
 * @class DirectionalLightNode DirectionalLightNode.h Scene/DirectionalLightNode.h
 */
class DirectionalLightNode : public LightNode {
    OE_SCENE_NODE(DirectionalLightNode, LightNode)

public:
    
    DirectionalLightNode();
    virtual ~DirectionalLightNode();

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<LightNode>(*this);
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::DirectionalLightNode)

#endif // _DIRECTIONAL_LIGHT_NODE_H_
