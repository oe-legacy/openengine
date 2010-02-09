// Light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_LIGHT_NODE_H_
#define _OE_LIGHT_NODE_H_

#include <Scene/ISceneNode.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Scene {

/**
 * Light tree node.
 * 
 * @class LightNode LightNode.h Scene/LightNode.h
 */
class LightNode : public ISceneNode {
    OE_SCENE_NODE(LightNode, ISceneNode)

public:
    bool active;
    Math::Vector<4,float> ambient, diffuse, specular;

    LightNode();
    virtual ~LightNode();
        
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & active;
        ar & ambient;
        ar & diffuse;
        ar & specular;
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::LightNode)

#endif // _OE_LIGHT_NODE_H_
