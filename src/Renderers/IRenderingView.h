// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_RENDERING_VIEW_H_
#define _INTERFACE_RENDERING_VIEW_H_

#include <Core/IListener.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Display/Viewport.h>
#include <Math/Vector.h>
#include <Renderers/IRenderer.h>
#include <Renderers/IRenderingView.h>

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Core::IListener;
using OpenEngine::Scene::ISceneNodeVisitor;
using OpenEngine::Display::Viewport;
using OpenEngine::Math::Vector;
using OpenEngine::Renderers::IRenderer;

/**
 * Rendering views are responsible for traversing and drawing the
 * scene in context of the view port it is bound to. This is done by
 * use of the visitor pattern [GoF 331] and the pre/post methods.
 *
 * Rendering views must be supplied with a view port and 
 * added to the renderer module in order to take effect.
 *
 * @class IRenderingView IRenderingView.h Renderers/IRenderingView.h
 *
 * @see Viewport
 * @see IRenderer
 * @see ISceneNodeVisitor
 */
class IRenderingView : public ISceneNodeVisitor, public IListener<RenderingEventArg> {
protected:

    Viewport& viewport;         //!< Viewport of this rendering view.

public:

    /**
     * Render a scene.
     *
     * @param renderer Current renderer.
     * @param root Root of scene to render.
     */
    virtual void Render(IRenderer* renderer, ISceneNode* root) = 0;

    /**
     * Create a rendering view bound to a view port.
     *
     * @param vp View port of rendering view
     */
    IRenderingView(Viewport& vp) : viewport(vp) {}

    /**
     * Default destructor.
     */
    virtual ~IRenderingView() {}

    /**
     * Get view port of the rendering view.
     *
     * @return View port of the rendering view
     */
    Viewport& GetViewport() {
        return viewport;
    }

    /**
     * Get the renderer that the view is processing for.
     *
     * @return Current renderer, NULL if no renderer processing is active.
     */
    virtual IRenderer* GetRenderer() = 0;

    /**
     * Processing hook
     */
    virtual void Handle(RenderingEventArg arg) = 0;

};


} // NS Renderers
} // NS OpenEngine

#endif
