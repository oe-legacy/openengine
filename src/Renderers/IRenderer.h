// Renderer interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_RENDERER_H_
#define _OE_INTERFACE_RENDERER_H_

#include <vector>
#include <Core/IEvent.h>
#include <Geometry/Line.h>
#include <Geometry/Face.h>
#include <Math/Vector.h>
#include <Utils/Timer.h>

#include <Display/IRenderCanvas.h>
#include <Core/IListener.h>

#include <list>

// forward declarations
namespace OpenEngine {
    namespace Display {
        class IViewingVolume;
    }
    namespace Resources{
        class FrameBuffer;
        class ITexture2D;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;
        class ITexture3D;
        typedef boost::shared_ptr<ITexture3D> ITexture3DPtr;
        class IDataBlock;
        typedef boost::shared_ptr<IDataBlock> IDataBlockPtr;
    }
}

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Core::IEvent;
using OpenEngine::Geometry::Line;
using OpenEngine::Geometry::FacePtr;
using OpenEngine::Math::Vector;
using OpenEngine::Utils::Time;
using OpenEngine::Resources::FrameBuffer;
using OpenEngine::Resources::ITexture2DPtr;
using OpenEngine::Resources::ITexture2D;
using OpenEngine::Resources::ITexture3DPtr;
using OpenEngine::Resources::ITexture3D;
using OpenEngine::Resources::IDataBlock;

using Core::IListener;
using Display::IRenderCanvas;

using std::list;

// forward declarations
class IRenderer;

/**
 * Event argument for all the rendering phases.
 *
 * @class RenderingEventArg IRenderer.h Renderers/IRenderer.h
 */
class RenderingEventArg {
public:
    IRenderCanvas& canvas;
    IRenderer& renderer;
    Time time;
    unsigned int approx;
    RenderingEventArg(IRenderCanvas& canvas, IRenderer& renderer, Time time = Time(), unsigned int approx = 0)
        : canvas(canvas), renderer(renderer), time(time), approx(approx) {}
};

class InitializeEventArg {
public:
    IRenderCanvas& canvas;
    InitializeEventArg(IRenderCanvas& canvas): canvas(canvas) {}
    virtual ~InitializeEventArg() {}
};

class DeinitializeEventArg {
public:
    IRenderCanvas& canvas;
    DeinitializeEventArg(IRenderCanvas& canvas): canvas(canvas) {}
    virtual ~DeinitializeEventArg() {}
};

class ProcessEventArg {
public:
    IRenderCanvas& canvas;
    Time start;                 //!< time of engine loop start.
    unsigned int approx;        //!< approximate engine loop time.
    ProcessEventArg(IRenderCanvas& canvas, Time start, unsigned int approx)
        : canvas(canvas)
        , start(start)
        , approx(approx) {}
    virtual ~ProcessEventArg() {}
};


/**
 * Renderer interface.
 *
 * Obsolete description:
 * This engine module is responsible for
 * rendering the scene as defined in all its Rendering Views.
 * The Renderer is the context using the RenderingView as its
 * strategy in terms of GOF (page 315).
 *
 * @class IRenderer IRenderer.h Renderers/IRenderer.h
 */
class IRenderer : public virtual IListener<Renderers::InitializeEventArg>, 
                  public virtual IListener<Renderers::DeinitializeEventArg>, 
                  public virtual IListener<Renderers::ProcessEventArg> {
// protected:
//     list<ICanvasListener*> dependencies;
public:

    /**
     * Rendering stages/phases.
     * A renderer will after construction be in the initialization
     * stage until the InitializeEvent has occurred and all listeners
     * have been processed. After that the phases will change after
     * completion of each event. Thus, if \a GetCurrentStage is invoked
     * by a listener of the \a ProcessEvent the result must be
     * \a RENDERER_PROCESS.
     */
    enum RendererStage {
		RENDERER_UNINITIALIZE,
        RENDERER_INITIALIZE,
        RENDERER_PREPROCESS,
        RENDERER_PROCESS,
        RENDERER_POSTPROCESS,
        RENDERER_DEINITIALIZE
    };

    /**
     * Event lists for the rendering phases.
     */
    virtual IEvent<RenderingEventArg>& InitializeEvent() = 0;
    virtual IEvent<RenderingEventArg>& PreProcessEvent() = 0;
    virtual IEvent<RenderingEventArg>& ProcessEvent() = 0;
    virtual IEvent<RenderingEventArg>& PostProcessEvent() = 0;
    virtual IEvent<RenderingEventArg>& DeinitializeEvent() = 0;

    /**
     * Default constructor.
     */
    IRenderer() : stage(RENDERER_UNINITIALIZE) {}

    /**
     * Destructor.
     */
    virtual ~IRenderer() {}

    /**
     * Get the current renderer stage.
     */
    virtual RendererStage GetCurrentStage() const {
        return stage;
    }

    /**
     * Apply a viewing volume.
     *
     * @param volume Viewing volume to apply
     */
    virtual void ApplyViewingVolume(Display::IViewingVolume& volume) = 0;

    /**
     * Load and Bind a texture.
     *
     * @param texr Texture resource
     */
    virtual void LoadTexture(ITexture2DPtr texr) = 0;
    virtual void LoadTexture(ITexture2D* texr) = 0;
    virtual void LoadTexture(ITexture3DPtr texr) = 0;
    virtual void LoadTexture(ITexture3D* texr) = 0;

    /**
     * Rebinds a texture, uploading any new changes.
     *
     * Requires the texture to be loaded if no data pointer is given.
     *
     * @param texr Texture resource
     */
    virtual void RebindTexture(ITexture2DPtr texr, unsigned int xOffset, unsigned int yOffset, unsigned int width, unsigned int height) = 0;
    virtual void RebindTexture(ITexture2D* texr, unsigned int xOffset, unsigned int yOffset, unsigned int width, unsigned int height) = 0;
    virtual void RebindTexture(ITexture3DPtr texr, unsigned int xOffset, unsigned int yOffset, unsigned int zOffset, unsigned int width, unsigned int height, unsigned int depth) = 0;
    virtual void RebindTexture(ITexture3D* texr, unsigned int xOffset, unsigned int yOffset, unsigned int zOffset, unsigned int width, unsigned int height, unsigned int depth) = 0;

    /**
     * Binds a framebuffer and all the textures attached.
     *
     * @param fb The frame buffer object.
     */
    virtual void BindFrameBuffer(FrameBuffer* fb) = 0;

    /**
     * Bind a buffer object.
     *
     * @param bo Buffer objct resource to be bound.
     */
    virtual void BindDataBlock(IDataBlock* bo) = 0;

    virtual void RebindDataBlock(Resources::IDataBlockPtr ptr, unsigned int start, unsigned int end) = 0;


    /**
     * Set the global background colour.
     * This is a product of OpenGL that treats the background colour
     * special, in that any change will modify the entire background
     * colour of the GL context.
     */
    virtual void SetBackgroundColor(Vector<4,float> color) = 0;

    /**
     * Get the global background colour.
     * This function is strongly related to OpenGL.
     * See \a SetBackgroundColor for an explanation.
     */
    virtual Vector<4,float> GetBackgroundColor() = 0;

    /**
     * Draw a face
     *
     * @param face Face to draw.
     */
    virtual void DrawFace(FacePtr face) = 0;

    /**
     * Draw a face (wire framed).
     *
     * @param face Face to draw.
     * @param color Color of lines.
     * @param width Width of lines [optional].
     */
    virtual void DrawFace(FacePtr face, Vector<3,float> color, float width = 1) = 0;

    /**
     * Draw a line.
     *
     * @param line Line to draw.
     * @param color Color of line.
     * @param width Width of line.
     */
    virtual void DrawLine(Line line, Vector<3,float> color, float width = 1) = 0;

    /**
     * Draw a point.
     *
     * @param point Point to draw.
     * @param color Color of point.
     * @param size Size of point.
     */
    virtual void DrawPoint(Vector<3,float> point, Vector<3,float> color , float size = 1) = 0;

    /**
     * Draw a sphere.
     *
     * @param center Center of sphere.
     * @param radius Radius of sphere.
     * @param color  Color of sphere.
     */
    virtual void DrawSphere(Vector<3,float> center, float radius, Vector<3,float> color) = 0;

    /**
     * Tests if Buffer Objects are supported.
     *
     * @return True if support is found.
     */
    virtual bool BufferSupport() = 0;

    /**
     * Are frame buffers supported.
     *
     * @return True if frame buffers are supported.
     */
    virtual bool FrameBufferSupport() = 0;

protected:
    RendererStage stage;

};

} // NS Renderers
} // NS OpenEngine

#endif // _OE_INTERFACE_RENDERER_H_
