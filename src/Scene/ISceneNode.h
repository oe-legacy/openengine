// Scene node interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_SCENE_NODE_H_
#define _OE_INTERFACE_SCENE_NODE_H_

#include <string>
#include <list>

#define OE_SCENE_NODE(klass, syper)                     \
public:                                                 \
virtual void Accept(ISceneNodeVisitor& v);              \
virtual ISceneNode* Clone() const;                      \
virtual const std::string GetNodeName() const;          \
virtual void SetNodeName(std::string name);             \
private:                                                \
  std::string nodeName;

namespace OpenEngine {
    namespace Resources {
        class IArchiveWriter;
        class IArchiveReader;
    }

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
public:
    //! List of sub nodes @todo Should be private
    std::list<ISceneNode*> subNodes;

    /**
     * Default constructor.
     */      
    ISceneNode();
    ISceneNode(const ISceneNode& node);

    /**
     * Default destructor.
     */
    virtual ~ISceneNode();

    /**
     * Get parent node.
     */
    virtual ISceneNode* GetParent();

    /**
     * Add a sub node.
     *
     * @param sub Sub node
     */
    virtual void AddNode(ISceneNode* sub);

    /**
     * Remove a sub node.
     *
     * @param sub Sub node
     */
    virtual void RemoveNode(ISceneNode* sub);

    /**
     * Visit all sub nodes of the scene node.
     *
     * @param visitor Node visitor
     */
    virtual void VisitSubNodes(ISceneNodeVisitor& visitor);

    /**
     * Delete a sub node.
     * No error occurs if the supplied node is not a sub node.
     * It is safe to delete nodes during traversal. The actual
     * deletion of a node might however be delayed. Causing undesired
     * traversal or other effects due to the delay.
     *
     * @param node Sub node.
     */
    virtual void DeleteNode(ISceneNode* node);

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
    virtual void ReplaceNode(ISceneNode* oldNode, ISceneNode* newNode);

    /**
     * Remove all sub nodes.
     * 
     * Identical to performing RemoveNode(node) for all sub nodes.
     */
    virtual void RemoveAllNodes();

    /**
     * Delete all sub nodes.
     * 
     * Identical to performing DeleteNode(node) for all sub nodes.
     */
    virtual void DeleteAllNodes();

    /**
     * Get sub node count.
     *
     * @return Number of sub nodes
     */
    virtual unsigned int GetNumberOfNodes();

    /**
     * Get a sub node by index.
     * Defaults to one and returns NULL if the index in question does
     * not exist.
     *
     * @param index Sub node index [default 0]
     * @return Node at index or NULL if out of bounds
     */
    virtual ISceneNode* GetNode(unsigned int index=0);


    virtual void SetNodeName(std::string name) {};

    /**
     * Get index of a node
     * @paren node Sub node
     * @return index of node or -1 if it doesn't exist
     */

    virtual int IndexOfNode(ISceneNode* node);

    /**
     * Get a string representation of the node.
     * There is no restriction on the representation. It should
     * however contain the node name.
     * If not overwritten \a ToString will return the class name of
     * the node.
     * Currently the output is used for the node content in the
     * \a DotVisitor.
     *
     * @return String representation.
     */
    virtual const std::string ToString() const;

    /**
     * Clone the scene.
     * This performs a deep copy of the node and recursively clones
     * all sub nodes.
     *
     * @return Deep clone of the scene
     */
    virtual ISceneNode* Clone() const = 0;

    /**
     * Get the class name of a node as a string literal.
     * @code
     * ISceneNode* node = new TransformationNode();
     * node->GetNodeName() // => "TransformationNode"
     * @endcode
     *
     * @return Node class name
     */
    virtual const std::string GetNodeName() const = 0;

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

    virtual void Serialize(Resources::IArchiveWriter& w);
    virtual void Deserialize(Resources::IArchiveReader& r);

private:

    //! The parent node
    ISceneNode* parent;

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
    std::list<QueuedNode> operationQueue;

    //! Height of the accept/visit stack.
    int acceptStack;

    void _RemoveNode(ISceneNode* sub);
    void _DeleteNode(ISceneNode* sub);

    // We currently need to have access to these methods in the definition of
    // accept in all sub type. Clients should however not use them!
#define SCENE_NODE(klass) friend class klass;
#include "SceneNodes.def"
#undef SCENE_NODE
    void IncAcceptStack();
    void DecAcceptStack();

};

} // NS Scene
} // NS OpenEngine


#endif // _OE_INTERFACE_SCENE_NODE_H_
