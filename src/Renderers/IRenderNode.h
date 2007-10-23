// Render node interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _RENDER_NODE_INTERFACE_H_
#define _RENDER_NODE_INTERFACE_H_

#include <Scene/ISceneNode.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Scene/SceneNode.h>
#include <Renderers/IRenderingView.h>

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Scene::SceneNode;
using OpenEngine::Scene::ISceneNode;
using OpenEngine::Scene::ISceneNodeVisitor;

/**
 * Render node.
 * A node that can hold or calculate infomation to be used
 * in the rendering phase of the engine.
 *
 * @class IRenderNode IRenderNode.h Renderers/IRenderNode.h
 *
 * @see ISceneNode
 * @see IRenderer
 */
class IRenderNode : public SceneNode {
public:
    /**
     * Apply the node, called by the renderer
     */
    virtual void Apply(IRenderingView* view) = 0;

    /**
     * Forward call to the specefic RenderNode
     */
    void Accept(ISceneNodeVisitor& visitor) {
        visitor.VisitRenderNode(this);
    }
};

} // NS Renderers
} // NS OpenEngine

#endif // _RENDER_NODE_INTERFACE_H_
