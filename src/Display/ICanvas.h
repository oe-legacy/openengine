// Canvas interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_CANVAS_H_
#define _INTERFACE_CANVAS_H_

#include <Core/Event.h>
#include <Utils/Timer.h>
#include <Logging/Logger.h>

#include <Display/IViewingVolume.h>

namespace OpenEngine {
    namespace Scene{
        class ISceneNode;
    }
namespace Display {

using Core::Event;
using Core::IListener;
using Utils::Time;

class ICanvas;

class ResizeEventArg {
public:
    ICanvas& canvas;
    ResizeEventArg(ICanvas& canvas): canvas(canvas) {}
    virtual ~ResizeEventArg() {}
};

/**
 * Signals that the canvas has been initialized and consequently
 * renderers can safely run their own initialization procedures.
 **/
class InitializeEventArg {
public:
    ICanvas& canvas;
    InitializeEventArg(ICanvas& canvas): canvas(canvas) {}
    virtual ~InitializeEventArg() {}
};

/**
 * Signals that the canvas is about to deinitialize itself and consequently
 * renderers must run their cleanup procedures.
 **/
class DeinitializeEventArg {
public:
    ICanvas& canvas;
    DeinitializeEventArg(ICanvas& canvas): canvas(canvas) {}
    virtual ~DeinitializeEventArg() {}
};

/**
 * Signals that the content of the canvas needs to be updated.
 **/
class RedrawEventArg {
public:
    ICanvas& canvas;
    Time start;                 //!< time of engine loop start.
    unsigned int approx;        //!< approximate engine loop time.
    RedrawEventArg(ICanvas& canvas, Time start, unsigned int approx)
        : canvas(canvas)
        , start(start)
        , approx(approx) {}
    virtual ~RedrawEventArg() {}
};

class ICanvasListener 
    : public virtual IListener<ResizeEventArg>
    , public virtual IListener<RedrawEventArg>
    , public virtual IListener<Display::InitializeEventArg>
    , public virtual IListener<Display::DeinitializeEventArg> 
{
public:
    virtual ~ICanvasListener() {}
};

class CanvasObservable {
protected:
    Event<ResizeEventArg> resizeEvent;
    Event<RedrawEventArg> redrawEvent;
    Event<InitializeEventArg> initEvent;
    Event<DeinitializeEventArg> deinitEvent;
public:
    virtual ~CanvasObservable() {}

    Event<ResizeEventArg>& ResizeEvent() { return resizeEvent; }
    Event<RedrawEventArg>& RedrawEvent() { return redrawEvent; }
    Event<InitializeEventArg>& InitializeEvent() { return initEvent; }
    Event<DeinitializeEventArg>& DeinitializeEvent() { return deinitEvent; }
    void Attach(ICanvasListener& listener) { 
        resizeEvent.Attach(listener);
        redrawEvent.Attach(listener);
        initEvent.Attach(listener);
        deinitEvent.Attach(listener);
    }
}; 
    
// class IRenderableSurface {
// protected:
//     IViewingVolume* vv;
//     ISceneNode* scene;
// public:
    
//     ~IRenderableSurface() {}
    
//     /**
//      * Get canvas width.
//      *
//      * @return Canvas width
//      */
//     virtual unsigned int GetWidth() const = 0;

//     /**
//      * Get canvas height.
//      *
//      * @return Canvas height
//      */
//     virtual unsigned int GetHeight() const = 0;
    
//     /**
//      * Get canvas depth.
//      *
//      * @return Canvas depth
//      */
//     virtual unsigned int GetDepth() const = 0;

//     /**
//      * Set canvas width.
//      * Must be supported as long as the module initialization method
//      * has not been invoked.
//      * After initialization the behavior is up to the implementation.
//      *
//      * @param width Canvas width
//      */
//     virtual void SetWidth(const unsigned int width) = 0;

//     /**
//      * Set canvas height.
//      * Must be supported as long as the module initialization method
//      * has not been invoked.
//      * After initialization the behavior is up to the implementation.
//      *
//      * @param height Canvas height
//      */
//     virtual void SetHeight(const unsigned int height) = 0;
    
//     /**
//      * Set canvas depth.
//      * Must be supported as long as the module initialization method
//      * has not been invoked.
//      * After initialization the behavior is up to the implementation.
//      *
//      * @param depth Canvas depth
//      */
//     virtual void SetDepth(const unsigned int depth) = 0;

//     /**
//      * Set the viewing volume (camera)
//      * This viewing volume will be passed to a renderer and used when
//      * creating the 3D-scene.
//      *
//      * @param vv The viewing volume
//      */
//     virtual void SetViewingVolume(IViewingVolume* vv) { this->vv = vv; }

//     /**
//      * Get the viewing volume (camera)
//      * This viewing volume will be passed to a renderer and used when
//      * creating the 3D-scene.
//      *
//      * @return The viewing volume
//      */
//     virtual IViewingVolume* GetViewingVolume() const { return vv; }

//     /**
//      * Set the root scene graph node.
//      * The scene root will be passed to a renderer and used when
//      * creating the 3D-scene.
//      *
//      * @param scene The scene graph root
//      */
//     virtual void SetScene(ISceneNode* scene) { this->scene = scene; }

//     /**
//      * Get the root scene graph node.
//      * The scene root will be passed to a renderer and used when
//      * creating the 3D-scene.
//      *
//      * @return The scene graph root
//      */
//     virtual ISceneNode* GetScene() const { return scene; }
// };

/**
 * Canvas interface.
 *
 * A canvas represents a two-dimensional off-screen surface, acting as
 * a target for one or more renderers.
 *
 * @class ICanvas ICanvas.h Display/ICanvas.h
 */
    class ICanvas: public CanvasObservable {//, public virtual IRenderableSurface {
protected:
    IViewingVolume* vv;
    ISceneNode* scene;
public:
    virtual ~ICanvas() {}    

    /**
     * Get canvas width.
     *
     * @return Canvas width
     */
    virtual unsigned int GetWidth() const = 0;

    /**
     * Get canvas height.
     *
     * @return Canvas height
     */
    virtual unsigned int GetHeight() const = 0;
    
    /**
     * Get canvas depth.
     *
     * @return Canvas depth
     */
    virtual unsigned int GetDepth() const = 0;

    /**
     * Set canvas width.
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @param width Canvas width
     */
    virtual void SetWidth(const unsigned int width) = 0;

    /**
     * Set canvas height.
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @param height Canvas height
     */
    virtual void SetHeight(const unsigned int height) = 0;
    
    /**
     * Set canvas depth.
     * Must be supported as long as the module initialization method
     * has not been invoked.
     * After initialization the behavior is up to the implementation.
     *
     * @param depth Canvas depth
     */
    virtual void SetDepth(const unsigned int depth) = 0;

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
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_CANVAS_H_
