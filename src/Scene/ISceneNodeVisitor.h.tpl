// Node visitor interface for scene nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

@OE_AUTOGEN_HEADER@

#ifndef _INTERFACE_SCENE_NODE_VISITOR_H_
#define _INTERFACE_SCENE_NODE_VISITOR_H_

namespace OpenEngine {

// forward declarations of node types
namespace Renderers {
class IRenderNode;
class RenderStateNode;
}

namespace Scene {
class ISceneNode;
class SceneNode;
class GeometryNode;
class TransformationNode;
class TerrainNode;

// generated forward declarations
@OE_VISITOR_HEADER_DECLARATION_EXPANSION@

using OpenEngine::Renderers::IRenderNode;
using OpenEngine::Renderers::RenderStateNode;

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

protected:
    // Default visiting behavior.
    virtual void DefaultVisitNode(ISceneNode* node);

public:
    ISceneNodeVisitor();
    virtual ~ISceneNodeVisitor();

    // Default visitor methods.
    // If not overwritten in sub types they will just invoke the
    // visitor on sub nodes.
    virtual void VisitSceneNode(SceneNode* node);
    virtual void VisitGeometryNode(GeometryNode* node);
    virtual void VisitTransformationNode(TransformationNode* node);
    virtual void VisitRenderStateNode(RenderStateNode* node);
    virtual void VisitRenderNode(IRenderNode* node);

// generated visit declerations
@OE_VISITOR_HEADER_EXPANSION@

};

} // NS Scene
} // NS OpenEngine

#endif // _INTERFACE_SCENE_NODE_VISITOR_H_
