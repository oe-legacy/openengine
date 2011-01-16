//
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include <Scene/ISceneNode.h>
#include <Scene/Exceptions.h>


namespace OpenEngine {
namespace Scene {

using std::list;

ISceneNode::ISceneNode()
    : parent(NULL)
    , acceptStack(0) {

}

ISceneNode::ISceneNode(const ISceneNode& node)
    : parent(NULL)
    , acceptStack(0)
{

}

ISceneNode::~ISceneNode() {
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        delete *itr;
    subNodes.clear();
}

ISceneNode* ISceneNode::GetParent() {
    return parent;
}

unsigned int ISceneNode::GetNumberOfNodes() {
    return subNodes.size();
}

ISceneNode* ISceneNode::GetNode(unsigned int index) {
    if (index >= GetNumberOfNodes())
        return NULL;
    list<ISceneNode*>::iterator itr = subNodes.begin();
    while (index--) itr++;
    return *itr;
}

int ISceneNode::IndexOfNode(ISceneNode* node) {
    int index = 0;
    for (list<ISceneNode*>::iterator itr = subNodes.begin();
         itr != subNodes.end();
         itr++) {

        if (*itr == node)
            return index;
        index++;
    }
    return -1;
}

const string ISceneNode::ToString() const {
    return this->GetTypeName() + string(" ") + this->GetInfo();
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
void ISceneNode::IncAcceptStack() {
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
void ISceneNode::DecAcceptStack() {
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
void ISceneNode::VisitSubNodes(ISceneNodeVisitor& visitor) {
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        (*itr)->Accept(visitor);
}

void ISceneNode::AddNode(ISceneNode* sub) {
    if (sub == NULL)
        throw InvalidSceneOperation("A scene node may not have a NULL child.");
    if (sub->parent != NULL)
        throw InvalidSceneOperation("A scene node may not have multiple parents.");
    subNodes.push_back(sub);
    sub->parent = this;
}

void ISceneNode::RemoveNode(ISceneNode* sub) {
    // if there is a accept in progress queue the operation
    if (acceptStack)
        operationQueue.push_back(QueuedNode(REMOVE_OP, sub));
    // else we can safely remove it right away
    else _RemoveNode(sub);
}

//! non-delayed removal of a node
void ISceneNode::_RemoveNode(ISceneNode* sub) {
    subNodes.remove(sub);
    sub->parent = NULL;
}

void ISceneNode::DeleteNode(ISceneNode* sub) {
    // if there is a accept in progress queue the operation
    if (acceptStack)
        operationQueue.push_back(QueuedNode(DELETE_OP, sub));
    // else we can safely delete it right away
    else _DeleteNode(sub);
}

//! non-delayed deletion of a node
void ISceneNode::_DeleteNode(ISceneNode* sub) {
    subNodes.remove(sub);
    delete sub;
}

void ISceneNode::ReplaceNode(ISceneNode* oldNode, ISceneNode* newNode) {
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

void ISceneNode::RemoveAllNodes() {
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

void ISceneNode::DeleteAllNodes() {
    // same as for RemoveAllNodes
    ISceneNode* node = NULL;
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++) {
        if (node) DeleteNode(node);
        node = *itr;
    }
    if (node) DeleteNode(node);
}

void ISceneNode::Serialize(Resources::IArchiveWriter& w) {
    throw Exception(GetTypeName() + " does not implement Serialize." );
}

void ISceneNode::Deserialize(Resources::IArchiveReader& r) {
    throw Exception(GetTypeName() + " does not implement Deserialize.");
}


} // NS Scene
} // NS OpenEngine
