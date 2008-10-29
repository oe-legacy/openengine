// Node visitor interface for scene nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_SCENE_NODE_VISITOR_H_
#define _OE_INTERFACE_SCENE_NODE_VISITOR_H_

namespace OpenEngine {
namespace Scene {

// Forward declare scene node interface
class ISceneNode;

// Forward declare all scene node implementations
#define SCENE_NODE(type) class type;
#include "SceneNodes.def"
#undef SCENE_NODE

/**
 * Node visitor interface for scene nodes.
 * The use of the visitor pattern lets us define new operations on the
 * scene node structure without modifying the structure itself. 
 * See [GoF 331] for detailed information.
 *
 * @class ISceneNodeVisitor ISceneNodeVisitor.h Scene/ISceneNodeVisitor.h
 *
 * @see ISceneNode
 */
class ISceneNodeVisitor {
public:
    ISceneNodeVisitor();
    virtual ~ISceneNodeVisitor();

    // Visitor methods.
    // If not overwritten in visitor implementations they will just
    // invoke DefaultVisitNode.
#define SCENE_NODE(type)                        \
    virtual void Visit##type(type* node);
#include "SceneNodes.def"
#undef SCENE_NODE

protected:
    // Default visiting behavior.
    virtual void DefaultVisitNode(ISceneNode* node);

};

} // NS Scene
} // NS OpenEngine

#endif // _INTERFACE_SCENE_NODE_VISITOR_H_
