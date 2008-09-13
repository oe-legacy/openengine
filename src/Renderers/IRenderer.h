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
#include <Core/IModule.h>
#include <Core/IEvent.h>
#include <Scene/ISceneNode.h>
#include <Geometry/Line.h>
#include <Geometry/Face.h>
#include <Math/Vector.h>
#include <Utils/Timer.h>
#include <Resources/ITextureResource.h>

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Core::IModule;
using OpenEngine::Core::IEvent;
using OpenEngine::Scene::ISceneNode;
using OpenEngine::Geometry::Line;
using OpenEngine::Geometry::FacePtr;
using OpenEngine::Math::Vector;
using OpenEngine::Utils::Time;
using OpenEngine::Resources::ITextureResourcePtr;

// forward declerations
class IRenderer; class IRenderingView;

/**
 *
 */
struct RenderingEventArg {
    IRenderer& renderer;
    Time time;
    unsigned int approx;
    RenderingEventArg(IRenderer& renderer, Time time = Time(), unsigned int approx = 0)
        : renderer(renderer), time(time), approx(approx) {}
};

/**
 * Renderer interface. This engine module is responsible for
 * rendering the scene as defined in all its Rendering Views.
 * The Renderer is the context using the RenderingView as its
 * strategy in terms of GOF (page 315).
 *
 * @class IRenderer IRenderer.h Renderers/IRenderer.h
 */
class IRenderer : public virtual IModule {

protected:

    //! root node of the rendering scene
    ISceneNode* root;

public:

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
    IRenderer() : root(NULL) {}

    /**
     * Destructor.
     */
    virtual ~IRenderer() {}

    /**
     * Set the root node for the rendering scene.
     *
     * @param root Scene root node
     * @return Old scene root
     */
    virtual ISceneNode* SetSceneRoot(ISceneNode* root) {
        ISceneNode* old = this->root;
        this->root = root;
        return old;
    }

    /**
     * Get the root node for the rendering scene.
     *
     * @return Scene root
     */
    virtual ISceneNode* GetSceneRoot() {
        return root;
    }

    /**
     * Load and Bind a texture.
     *
     * @param texr Texture resource
     */
    virtual void LoadTexture(ITextureResourcePtr texr) = 0;

    /**
     * Bind or rebind a texture.
     *
     * @param texr Texture resource
     */
    virtual void RebindTexture(ITextureResourcePtr texr) = 0;

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

};

} // NS Renderers
} // NS OpenEngine

#endif // _OE_INTERFACE_RENDERER_H_
