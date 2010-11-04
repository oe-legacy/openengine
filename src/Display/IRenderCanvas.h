// Renderable canvas interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_RENDER_CANVAS_H_
#define _INTERFACE_RENDER_CANVAS_H_

#include <Display/ICanvas.h>

namespace OpenEngine {
    namespace Scene {
        class ISceneNode;
    }
    namespace Renderers {
        class IRenderer;
    }
namespace Display {
   
class IViewingVolume;
class ICanvasBackend;
using Renderers::IRenderer;
using Scene::ISceneNode;


/**
 * Renderable canvas interface.
 *
 * A renderable canvas takes a scene, a viewing volume, and a
 * renderer and produces a two-dimensional image.
 *
 * @class ICanvas ICanvas.h Display/ICanvas.h
 */
class IRenderCanvas: public ICanvas {
protected:
    IViewingVolume* vv;
    ISceneNode* scene;
    IRenderer* renderer;
public:
    IRenderCanvas(): ICanvas(), vv(NULL), scene(NULL), renderer(NULL) {}
    IRenderCanvas(ICanvasBackend* backend): ICanvas(backend), vv(NULL), scene(NULL), renderer(NULL) {}
    // IRenderCanvas(): vv(NULL), scene(NULL), renderer(NULL) {}
    virtual ~IRenderCanvas() {}

    /**
     * Set the viewing volume (camera)
     * This viewing volume will be passed to a renderer and used when
     * rendering the scene.
     *
     * @param vv The viewing volume
     */
    virtual void SetViewingVolume(IViewingVolume* vv) { this->vv = vv; }

    /**
     * Get the viewing volume (camera)
     * This viewing volume will be passed to a renderer and used when
     * rendering the scene.
     *
     * @return The viewing volume
     */
    virtual IViewingVolume* GetViewingVolume() const { return vv; }

    /**
     * Set the root scene graph node.
     * The scene root will be passed to a renderer and used when
     * rendering the scene.
     *
     * @param scene The scene graph root
     */
    virtual void SetScene(ISceneNode* scene) { this->scene = scene; }

    /**
     * Get the root scene graph node.
     * The scene root will be passed to a renderer and used when
     * rendering the scene.
     *
     * @return The scene graph root
     */
    virtual ISceneNode* GetScene() const { return scene; }

    /**
     * Set the renderer.
     *
     * @param renderer The renderer
     */
    virtual void SetRenderer(IRenderer* renderer) {
        this->renderer = renderer;
    }

    /**
     * Get the renderer.
     *
     * @return The renderer
     */
    virtual IRenderer* GetRenderer() {
        return renderer;
    }
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_CANVAS_H_
