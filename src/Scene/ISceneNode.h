// Scene node interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_SCENE_NODE_H_
#define _INTERFACE_SCENE_NODE_H_

#include <list>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>

#include <boost/serialization/export.hpp>

namespace OpenEngine {
namespace Scene {

// forward declaration
class ISceneNodeVisitor;

/**
 * Scene node interface.
 * A scene node is an element in the engine scene graph. It implements
 * the subject part of the visitor pattern [GoF 331] and it can
 * contain references to sub nodes making it a composite object too
 * [GoF 163].
 *
 * @class ISceneNode ISceneNode.h Scene/ISceneNode.h
 *
 * @see ISceneNodeVisitor
 * @see ISceneGraph
 * @see SceneNode
 */
class ISceneNode {

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & subNodes;
    }

    friend class SceneNode;

protected:
    //! The parent node
    ISceneNode* parent;

public:
    //! List of sub nodes
    std::list<ISceneNode*> subNodes;

    /**
     * Default constructor.
     */      
    ISceneNode() : parent(NULL) {};

    /**
     * Default destructor.
     */
    virtual ~ISceneNode() {};

    /**
     * Get parent node.
     */
    virtual ISceneNode* GetParent() = 0;

    /**
     * Add a sub node.
     *
     * @param sub Sub node
     */
    virtual void AddNode(ISceneNode* sub) = 0;

    /**
     * Remove a sub node.
     *
     * @param sub Sub node
     */
    virtual void RemoveNode(ISceneNode* sub) = 0;

    /**
     * Visit all sub nodes of the scene node.
     *
     * @param visitor Node visitor
     */
    virtual void VisitSubNodes(ISceneNodeVisitor& visitor) = 0;

    /**
     * Accept a visitor.
     * To perform the visitor operation one must call 
     * @code visitor.Visit(this); @endcode
     *
     * The accept implementation is responsible for traversing the
     * connected sub nodes if desired.
     *
     * @param visitor Node visitor
     *
     * @see ISceneNodeVisitor
     */
    virtual void Accept(ISceneNodeVisitor& visitor) = 0;

    /**
     * Delete a sub node.
     * No error occurs if the supplied node is not a sub node.
     * It is safe to delete nodes during traversal. The actual
     * deletion of a node might however be delayed. Causing undesired
     * traversal or other effects due to the delay.
     *
     * @param node Sub node.
     */
    virtual void DeleteNode(ISceneNode* node) = 0;

    /**
     * Replace a sub node.
     *
     * The replaced node will be deleted after a successful
     * replacement. 
     *
     * No error occurs if the supplied node is not a sub node.
     * It is safe to replace nodes during traversal.
     *
     * The actual deletion of the replaced node might however be
     * delayed.
     *
     * @param oldNode Sub node to be replaced (deleted).
     * @param newNode Sub node to be replaced by (added).
     */
    virtual void ReplaceNode(ISceneNode* oldNode, ISceneNode* newNode) = 0;

    /**
     * Remove all sub nodes.
     * 
     * Identical to performing RemoveNode(node) for all sub nodes.
     */
    virtual void RemoveAllNodes() = 0;

    /**
     * Delete all sub nodes.
     * 
     * Identical to performing DeleteNode(node) for all sub nodes.
     */
    virtual void DeleteAllNodes() = 0;

    /**
     * Clone the scene.
     * This performs a deep copy of the node and recursively clones
     * all sub nodes.
     *
     * @return Deep clone of the scene
     */
    virtual ISceneNode* Clone() = 0;

    /**
     * Get sub node count.
     *
     * @return Number of sub nodes
     */
    virtual int GetNumberOfNodes() = 0;
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::ISceneNode)


#endif // _INTERFACE_SCENE_NODE_H_
