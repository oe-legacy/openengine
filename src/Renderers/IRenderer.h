// Renderer interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_RENDERER_H_
#define _INTERFACE_RENDERER_H_

#include <vector>
#include <Core/IModule.h>
#include <Core/Event.h>
#include <Scene/ISceneNode.h>
#include <Geometry/Line.h>
#include <Geometry/Face.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Core::IModule;
using OpenEngine::Core::Event;
using OpenEngine::Scene::ISceneNode;
using OpenEngine::Geometry::Line;
using OpenEngine::Geometry::FacePtr;
using OpenEngine::Math::Vector;
using namespace std;

// Forward declaration
class IRenderer;
class IRenderingView;

/**
 *
 */
struct RenderingEventArg {
    IRenderer& renderer;
    float dt;
};

/**
 * Renderer interface. This engine module is responsible for
 * rendering the scene as defined in all its RenderingViews.
 * The Renderer is the context using the RenderingView as its
 * strategy in terms of GOF (page 315).
 *
 * @class IRenderer IRenderer.h Renderers/IRenderer.h
 */
class IRenderer : public virtual IModule {
protected:
    //! list of rendering views
    //list<IRenderingView*> vRenderingView;

    //! root node of the rendering scene
    ISceneNode* root;

public:

    /**
     * Rendering phases.
     */
    Event<RenderingEventArg> initialize;
    Event<RenderingEventArg> preProcess;
    Event<RenderingEventArg> process;
    Event<RenderingEventArg> postProcess;
    Event<RenderingEventArg> deinitialize;

    /**
     * Default constructor.
     */
    IRenderer() : root(NULL) {}

    /**
     * Destructor.
     */
    virtual ~IRenderer() {}

    //! @see EModule::IsTypeOf()
    bool IsTypeOf(const std::type_info& inf) { 
        return typeid(IRenderer) == inf; 
    }

    /**
     * Set the root node for the rendering scene.
     *
     * @param root Scene root node
     * @return Old scene root
     */
    ISceneNode* SetSceneRoot(ISceneNode* root) {
        ISceneNode* old = this->root;
        this->root = root;
        return old;
    }

    /**
     * Get the root node for the rendering scene.
     *
     * @return Scene root
     */
    ISceneNode* GetSceneRoot() {
        return root;
    }

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
     * Set far clipping plane for rendering.
     * This specifies a different far clipping plane then for the
     * active viewing volume, allowing sky box rendering.
     *
     * @param farPlane Far clipping plane.
     */
    virtual void SetFarPlane(float farPlane) = 0;

    /**
     * Get the current far clipping plane for rendering.
     * If it is not set 0 is returned.
     *
     * @return farPlane Far clipping plane.
     */
    virtual float GetFarPlane() = 0;

};

} // NS Renderers
} // NS OpenEngine

#endif // _INTERFACE_RENDERER_H_
