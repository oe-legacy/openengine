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

#include <Utils/Timer.h>
#include <Resources/ITexture2D.h>
#include <Core/IListener.h>
#include <Math/Vector.h>
#include <Display/ICanvasBackend.h>

namespace OpenEngine {
namespace Display {

// using Core::Event;
using Core::IListener;
using Utils::Time;
using Math::Vector;
using namespace Resources;

class ICanvas;

class ResizeEventArg {
public:
    ICanvas& canvas;
    ResizeEventArg(ICanvas& canvas): canvas(canvas) {}
    virtual ~ResizeEventArg() {}
};

class InitializeEventArg {
public:
    ICanvas& canvas;
    InitializeEventArg(ICanvas& canvas): canvas(canvas) {}
    virtual ~InitializeEventArg() {}
};

class DeinitializeEventArg {
public:
    ICanvas& canvas;
    DeinitializeEventArg(ICanvas& canvas): canvas(canvas) {}
    virtual ~DeinitializeEventArg() {}
};

class ProcessEventArg {
public:
    ICanvas& canvas;
    Time start;                 //!< time of engine loop start.
    unsigned int approx;        //!< approximate engine loop time.
    ProcessEventArg(ICanvas& canvas, Time start, unsigned int approx)
        : canvas(canvas)
        , start(start)
        , approx(approx) {}
    virtual ~ProcessEventArg() {}
};

/**
 * Canvas interface.
 *
 * A canvas represents a two-dimensional off-screen surface.
 * 
 *
 * @class ICanvas ICanvas.h Display/ICanvas.h
 */
class ICanvas
    : public virtual IListener<Display::ResizeEventArg>
    , public virtual IListener<Display::ProcessEventArg>
    , public virtual IListener<Display::InitializeEventArg>
    , public virtual IListener<Display::DeinitializeEventArg> 
{
protected:
    Vector<2,int> pos;
    ICanvasBackend* backend;
public:
    ICanvas(): backend(NULL) {}
    ICanvas(ICanvasBackend* backend): backend(backend) {}
    virtual ~ICanvas() {
        if (backend)
            delete backend;
    }    

    /**
     * Get the origin position of the canvas.  
     *
     * This is only relevant when multiple canvases are composited
     * onto a target canvas.
     *
     * @return Canvas position
     */
    virtual Vector<2,int> GetPosition() const { return pos; }

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
     * Set the origin position of the canvas.  
     *
     * This is only relevant when multiple canvases are composited
     * onto a target canvas.
     *
     * @param position The canvas position
     */
    virtual void SetPosition(const Vector<2,int> pos) { this->pos = pos; };

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
     * Get canvas texture.  
     *
     * Get a texture representing the current contents of the canvas.
     * For now the texture is assumed to be bound by OpenGL and reside
     * only on the GPU.
     *
     * @return The canvas texture
     */
    virtual ITexture2DPtr GetTexture() = 0;
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_CANVAS_H_
