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
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Scene {

SceneNode::SceneNode() {
    parent = NULL;
}

SceneNode::~SceneNode() {
}

void SceneNode::Accept(ISceneNodeVisitor& visitor) {
    visitor.VisitSceneNode(this);
}
    
ISceneNode* SceneNode::GetParent() {
    return parent;
}

void SceneNode::SetParent(ISceneNode* node) {
    if(parent!=NULL)
        logger.warning << "parent overwrited" << logger.end;
    parent = node;
}

void SceneNode::VisitSubNodes(ISceneNodeVisitor& visitor) {
    list<ISceneNode*>::iterator itr;
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        (*itr)->Accept(visitor);
}

void SceneNode::AddNode(ISceneNode* sub) {
    if (sub == NULL) return;
    subNodes.push_back(sub);
    sub->SetParent(this);
}

void SceneNode::RemoveNode(ISceneNode* sub) {
    subNodes.remove(sub);
}

} // NS Scene
} // NS OpenEngine
