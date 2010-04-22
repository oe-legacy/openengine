// Rendering module and scene traverser
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
#include <Renderers/IRenderer.h>

namespace OpenEngine {
namespace Renderers {

using Core::IListener;
using Scene::ISceneNodeVisitor;
using Renderers::RenderingEventArg;

/**
 * Rendering views are responsible for traversing and drawing the
 * scene. This is done by use of the visitor pattern [GoF 331] and the
 * pre/post methods.
 *
 * A rendering view is simply a scene traverser which can receive
 * events from the renderer.
 *
 * @class IRenderingView IRenderingView.h Renderers/IRenderingView.h
 *
 * @see IRenderer
 * @see ISceneNodeVisitor
 */
class IRenderingView : public virtual ISceneNodeVisitor, public virtual IListener<RenderingEventArg> {
public:
    /**
     * Default destructor.
     */
    virtual ~IRenderingView() {}
};

} // NS Renderers
} // NS OpenEngine

#endif
