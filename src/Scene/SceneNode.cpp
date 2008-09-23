// Base class for scene nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/SceneNode.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Scene/Exceptions.h>

namespace OpenEngine {
namespace Scene {

using std::list;

SceneNode::SceneNode()
    : ISceneNode(),
      acceptStack(0) {
    
}

/**
 * Copy constructor.
 * Performs a shallow copy.
 *
 * @param node Node to copy.
 */
SceneNode::SceneNode(SceneNode& node) : ISceneNode(node) {
    // the copy constructor does not copy the sub nodes.
}

SceneNode::~SceneNode() {
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        delete *itr;
    subNodes.clear();
}

void SceneNode::Accept(ISceneNodeVisitor& visitor) {
    // visit the node
    visitor.VisitSceneNode(this);
}
    
ISceneNode* SceneNode::GetParent() {
    return parent;
}

/**
 * Increment the accept/visit stack.
 *
 * This should be invoked once before accepting on sub nodes. Sub
 * classes that overwrite the VisitSubNodes method are responsible for
 * invoking this.
 *
 * @see VisitSubNodes
 */
void SceneNode::IncAcceptStack() {
    // increment the accept stack
    ++acceptStack;
}

/**
 * Decrement the accept/visit stack.
 * If the stack counter is zero all queued operations are performed.
 *
 * This should be invoked once after accepting on sub nodes. Sub
 * classes that overwrite the VisitSubNodes method are responsible for
 * invoking this.
 *
 * @see VisitSubNodes
 */
void SceneNode::DecAcceptStack() {
    // if the accept stack is exhausted perform actions on all nodes
    // that were queued 
    if (--acceptStack == 0) {
        list<QueuedNode>::iterator q;
        for (q = operationQueue.begin(); q != operationQueue.end(); q++) {
            ISceneNode* node = (*q).node;
            QueueType type = (*q).type;
            if      (type == DELETE_OP) _DeleteNode(node);
            else if (type == REMOVE_OP) _RemoveNode(node);
        }
        operationQueue.clear();
    }
}

/**
 * Visit all child nodes.
 *
 * If overwriting this method in a sub class remember to increment and
 * decrement the accept stack in order to maintain the integrity of
 * the structure under tree traversal.
 * @see IncAcceptStack
 * @see DecAcceptStack
 *
 * @param visitor Visitor to traverse with.
 */
void SceneNode::VisitSubNodes(ISceneNodeVisitor& visitor) {
    IncAcceptStack();
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        (*itr)->Accept(visitor);
    DecAcceptStack();
}

void SceneNode::AddNode(ISceneNode* sub) {
    if (sub == NULL)
        throw InvalidSceneOperation("A scene node may not have a NULL child.");
    if (sub->parent != NULL)
        throw InvalidSceneOperation("A scene node may not have multiple parents.");
    subNodes.push_back(sub);
    sub->parent = this;
}

void SceneNode::RemoveNode(ISceneNode* sub) {
    // if there is a accept in progress queue the operation
    if (acceptStack)
        operationQueue.push_back(QueuedNode(REMOVE_OP, sub));
    // else we can safely remove it right away
    else _RemoveNode(sub);
}

//! non-delayed removal of a node
void SceneNode::_RemoveNode(ISceneNode* sub) {
    subNodes.remove(sub);
    sub->parent = NULL;
}

void SceneNode::DeleteNode(ISceneNode* sub) {
    // if there is a accept in progress queue the operation
    if (acceptStack)
        operationQueue.push_back(QueuedNode(DELETE_OP, sub));
    // else we can safely delete it right away
    else _DeleteNode(sub);
}

//! non-delayed deletion of a node
void SceneNode::_DeleteNode(ISceneNode* sub) {
    subNodes.remove(sub);
    delete sub;
}

void SceneNode::ReplaceNode(ISceneNode* oldNode, ISceneNode* newNode) {
    if (newNode == NULL)
        throw InvalidSceneOperation("Scene nodes may not have NULL children.");
    if (newNode->parent != NULL)
        throw InvalidSceneOperation("Scene nodes may not have multiple parents.");
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++) {
        if (*itr == oldNode) {
            newNode->parent = this;
            *itr = newNode;
            if (acceptStack)
                operationQueue.push_back(QueuedNode(DELETE_OP, oldNode));
            else _DeleteNode(oldNode);
            return;
        }
    }
}

void SceneNode::RemoveAllNodes() {
    // invariant - node is the last seen node in the list but never
    // the node contained by the current iterator.
    ISceneNode* node = NULL;
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++) {
        if (node) RemoveNode(node);
        node = *itr;
    }
    if (node) RemoveNode(node);
}

void SceneNode::DeleteAllNodes() {
    // same as for RemoveAllNodes
    ISceneNode* node = NULL;
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++) {
        if (node) DeleteNode(node);
        node = *itr;
    }
    if (node) DeleteNode(node);
}

ISceneNode* SceneNode::Clone() {
    ISceneNode* clone = CloneSelf();
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        clone->AddNode((*itr)->Clone());
    return clone;
}

/**
 * Deep clone the node.
 * CloneSelf is a helper function so sub types can avoid implementing
 * the full Clone method.
 *
 * @warning CloneSelf must clone only the node itself, NOT the sub nodes.
 *
 * @return Deep clone of (only) the node
 */
ISceneNode* SceneNode::CloneSelf() {
    return new SceneNode(*this);
}

int SceneNode::GetNumberOfNodes() {
    return subNodes.size();
}

} // NS Scene
} // NS OpenEngine
