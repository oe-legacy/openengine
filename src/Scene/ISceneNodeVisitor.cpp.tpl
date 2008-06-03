// Node visitor interface for scene graph nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

@OE_AUTOGEN_HEADER@

#include <Scene/ISceneNodeVisitor.h>
#include <Scene/SceneNode.h>
#include <Scene/GeometryNode.h>
#include <Scene/TransformationNode.h>
#include <Scene/PointLightNode.h>
#include <Scene/DirectionalLightNode.h>
#include <Renderers/RenderStateNode.h>
#include <Renderers/IRenderNode.h>

// generated include statements
@OE_VISITOR_IMPL_INCLUDE_EXPANSION@

namespace OpenEngine {
namespace Scene {

    //! Default constructor.
    ISceneNodeVisitor::ISceneNodeVisitor() {}

    //! Default destructor.
    ISceneNodeVisitor::~ISceneNodeVisitor() {}

    /**
     * Default visit behavior.
     * When a visit method is not implemented for a node type this
     * method is invoked. By default it invokes the VisitSubNodes on
     * the current node, that usually visits all of its children.
     *
     * @param node The visited scene node
     */
    void ISceneNodeVisitor::DefaultVisitNode(ISceneNode* node) {
        node->VisitSubNodes(*this);
    }

    /**
     * Process the concrete algorithm on the visited node.
     * This method is called from somewhere in the visited nodes
     * accept method.
     * If not overwritten in a sub-type, this method will invoke the
     * VisitSubNodes method that by default just forward the visitor
     * to sub nodes.
     *
     * @see IGraphNode::Accept()
     * @see DefaultVisitNode(ISceneNode*)
     * @param node Pointer to the visited node
     */
    void ISceneNodeVisitor::VisitSceneNode(SceneNode* node) {
        DefaultVisitNode(node);
    }
    //! @see VisitSceneNode
    void ISceneNodeVisitor::VisitGeometryNode(GeometryNode* node) {
        DefaultVisitNode(node);
    }
    //! @see VisitSceneNode
    void ISceneNodeVisitor::VisitTransformationNode(TransformationNode* node) {
        DefaultVisitNode(node);
    }
    //! @see VisitSceneNode
    void ISceneNodeVisitor::VisitRenderStateNode(RenderStateNode* node) {
        DefaultVisitNode(node);
    }
    //! @see VisitSceneNode
    void ISceneNodeVisitor::VisitRenderNode(IRenderNode* node) {
        DefaultVisitNode(node);
    }
    //! @see VisitSceneNode
    void ISceneNodeVisitor::VisitPointLightNode(PointLightNode* node) { 
        DefaultVisitNode(node); 
    }
    //! @see  VisitSceneNode
    void ISceneNodeVisitor::VisitDirectionalLightNode(DirectionalLightNode* node) { 
        DefaultVisitNode(node); 
    }


// generated default visit implementations
@OE_VISITOR_IMPL_EXPANSION@

} // NS Scene
} // NS OpenEngine
