// Node visitor interface for scene graph nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/ISceneNodeVisitor.h>
#include <Scene/ISceneNode.h>
#include <Scene/SceneNodes.h>

namespace OpenEngine {
namespace Scene {

    //! Default constructor.
    ISceneNodeVisitor::ISceneNodeVisitor() {}

    //! Default destructor.
    ISceneNodeVisitor::~ISceneNodeVisitor() {}

    /**
     * Process the concrete algorithm on the visited node.
     * This method is called from the visited nodes accept method.
     * If not overwritten in a sub-type, this method will invoke the
     * \a VisitSubNodes method (through \a DefaultVisitNode) that just
     * forwards the visitor to sub nodes.
     *
     * @see ISceneNode::Accept()
     * @param node Pointer to the visited node
     */
#define SCENE_NODE(type)                              \
    void ISceneNodeVisitor::Visit##type(type* node) { \
        DefaultVisitNode(node);                       \
    }
#include "SceneNodes.def"
#undef SCENE_NODE

    /**
     * Default visiting behavior.
     * Changing this will change the tree traversal.
     * By default it will visit sub nodes in a depth-first traversal.
     *
     * @code
     * // Creating a visitor that goes up the parent chain
     * class AncestorVisitor : public ISceneNodeVisitor {
     * protected:
     *   void DefaultVisitNode(ISceneNode* node) {
     *     if (node->GetParent() != NULL)
     *       node->GetParent()->Accept(*this);
     *   }
     * public:
     *   void VisitGeometryNode(GeometryNode* node) {
     *     logger.info << "Found a geometry node among the ancestors."
     *                 << logger.end;
     *     DefaultVisitNode(node); // keep traversing the parent chain
     *   }
     * };
     * @endcode
     *
     * @todo:
     *   we could get rid of this by creating distinct visitor base
     *   classes. Such as depth-first, parent-tree and so on. 
     *   We might also want to look into read-only visitors so we can
     *   avoid the operation queue.
     */
    void ISceneNodeVisitor::DefaultVisitNode(ISceneNode* node) {
        node->VisitSubNodes(*this);
    }

} // NS Scene
} // NS OpenEngine
