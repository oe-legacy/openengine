// Light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _LIGHT_NODE_H_
#define _LIGHT_NODE_H_

#include <Scene/SceneNode.h>
#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>

#include <Scene/ISceneNodeVisitor.h>
#include <Math/Vector.h>

// forward declarations
namespace OpenEngine {
namespace Scene {

using namespace OpenEngine::Scene;
using namespace OpenEngine::Math;

/**
 * Light tree node.
 * 
 * 
 * @class LightNode LightNode.h Scene/LightNode.h
 */
class LightNode : public SceneNode {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<SceneNode>(*this);
        ar & active;
        ar & ambient;
        ar & diffuse;
        ar & specular;
    }

public:
    LightNode();
    virtual ~LightNode() {}
    
    bool active;
    Vector<4,float> ambient, diffuse, specular;
    
    
    //! Accept of visitors
    void Accept(ISceneNodeVisitor& v) = 0;
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::LightNode)

#endif // _LIGHT_NODE_H_
