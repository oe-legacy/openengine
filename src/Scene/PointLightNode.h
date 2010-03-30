// Positional light node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_POINT_LIGHT_NODE_H_
#define _OE_POINT_LIGHT_NODE_H_

#include <Geometry/Light.h>
#include <Scene/ISceneNode.h>

namespace OpenEngine {
namespace Scene {

using Geometry::Light;

/**
 * Point Light tree node.
 * 
 * 
 * @class PointLightNode PointLightNode.h Scene/PointLightNode.h
 */
class PointLightNode : public Light, public ISceneNode {
    OE_SCENE_NODE(PointLightNode, ISceneNode)
public:
    float constAtt, linearAtt, quadAtt;

    PointLightNode();
    virtual ~PointLightNode();

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<Light>(*this);
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & constAtt;
        ar & linearAtt;
        ar & quadAtt;
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::PointLightNode)

#endif // _OE_POINT_LIGHT_NODE_H_
