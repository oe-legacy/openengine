// Render node interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_RENDER_NODE_H_
#define _OE_RENDER_NODE_H_

#include <Scene/ISceneNode.h>
#include <Renderers/IRenderingView.h>

namespace OpenEngine {
namespace Scene {

/**
 * Render node.
 * A node that can hold or calculate infomation to be used
 * in the rendering phase of the engine.
 *
 * @class RenderNode RenderNode.h Scene/RenderNode.h
 *
 * @see ISceneNode
 * @see IRenderer
 */
class RenderNode : public ISceneNode {
    OE_SCENE_NODE(RenderNode, ISceneNode)

public:
    /**
     * Apply the node, called by the renderer
     */
    virtual void Apply(Renderers::IRenderingView* view) /* = 0; (prohibited by Clone) */ {}
};

} // NS Scene
} // NS OpenEngine

#endif // _OE_RENDER_NODE_H_
