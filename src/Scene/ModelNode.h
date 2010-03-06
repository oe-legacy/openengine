// Model node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MODEL_NODE_H_
#define _OE_MODEL_NODE_H_

#include <Scene/ISceneNode.h>

namespace OpenEngine {
    namespace Geometry {
        class Model;
    }
namespace Scene {

using Geometry::Model;

/**
 * Model node.
 * 
 * 
 * @class ModelNode ModelNode.h Scene/ModelNode.h
 */
class ModelNode : public ISceneNode {
    OE_SCENE_NODE(ModelNode, ISceneNode)

public:
    Model* model;

    ModelNode() { model = NULL; }
    ModelNode(Model* model);
    virtual ~ModelNode();

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

BOOST_CLASS_EXPORT(OpenEngine::Scene::ModelNode)

#endif // _OE_MODEL_NODE_H_
