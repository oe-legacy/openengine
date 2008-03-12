// Base class for scene nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include <Scene/ISceneNode.h>
#include <Scene/ISceneNodeVisitor.h>
#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>

namespace OpenEngine {
namespace Scene {

/**
 * Base class for scene nodes.
 *
 * @class SceneNode SceneNode.h Scene/SceneNode.h
 */
class SceneNode : public ISceneNode {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
    }


protected:
    //! Queue operation types.
    enum QueueType { DELETE_OP, REMOVE_OP };
    //! Wrapper for a node queued for later operation.
    struct QueuedNode {
        QueueType type;         //!< operation type
        ISceneNode* node;       //!< client node
        //! Queue operation constructor.
        QueuedNode(QueueType t, ISceneNode* n) : type(t), node(n) {}
    };
    //! Queued node operations.
    list<QueuedNode> operationQueue;
    //! Height of the accept/visit stack.
    int acceptStack;

    void _RemoveNode(ISceneNode* sub);
    void _DeleteNode(ISceneNode* sub);

    void IncAcceptStack();
    void DecAcceptStack();

    virtual ISceneNode* CloneSelf();

public:
    SceneNode();
    SceneNode(SceneNode& node);
    virtual ~SceneNode();
    ISceneNode* GetParent();
    void AddNode(ISceneNode* sub);
    void RemoveNode(ISceneNode* sub);
    void VisitSubNodes(ISceneNodeVisitor& visitor);
    void Accept(ISceneNodeVisitor& visitor);

    void DeleteNode(ISceneNode* node);
    void ReplaceNode(ISceneNode* oldNode, ISceneNode* newNode);

    void RemoveAllNodes();
    void DeleteAllNodes();

    ISceneNode* Clone();

    int GetNumberOfNodes();
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::SceneNode);


#endif // _SCENE_NODE_H_
