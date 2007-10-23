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

namespace OpenEngine {
namespace Scene {

// forward declaration
class ISceneNodeVisitor;

using std::list;

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
protected:
    //! The parent node
    ISceneNode* parent;

public:
    //! List of sub nodes
    list<ISceneNode*> subNodes;

    /**
     * Default constructor.
     */      
    ISceneNode() {};

    /**
     * Default destructor.
     */
    virtual ~ISceneNode() {};

    /**
     * Set parent node.
     */
    virtual void SetParent(ISceneNode* node) = 0;

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

};

} // NS Scene
} // NS OpenEngine

#endif // _INTERFACE_SCENE_NODE_H_
