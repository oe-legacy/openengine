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

namespace OpenEngine {
namespace Scene {

/**
 * Base class for scene nodes.
 *
 * @class SceneNode SceneNode.h Scene/SceneNode.h
 */
class SceneNode : public ISceneNode {
public:
    SceneNode();
    virtual ~SceneNode();
    void SetParent(ISceneNode* node);
    ISceneNode* GetParent();
    void AddNode(ISceneNode* sub);
    void RemoveNode(ISceneNode* sub);
    void VisitSubNodes(ISceneNodeVisitor& visitor);
    void Accept(ISceneNodeVisitor& visitor);
};

} // NS Scene
} // NS OpenEngine

#endif // _SCENE_NODE_H_
