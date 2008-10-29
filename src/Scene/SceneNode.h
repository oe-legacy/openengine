// A scene node stub.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SCENE_NODE_H_
#define _OE_SCENE_NODE_H_

#include <Scene/ISceneNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Base class for scene nodes.
 *
 * @class SceneNode SceneNode.h Scene/SceneNode.h
 */
class SceneNode : public ISceneNode {
    OE_SCENE_NODE(SceneNode, ISceneNode)

public:
    SceneNode();
    SceneNode(const SceneNode& node);
    virtual ~SceneNode();

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::SceneNode);


#endif // _SCENE_NODE_H_
