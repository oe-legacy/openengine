// Frustum viewing volume.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_FRUSTUM_H_
#define _OE_FRUSTUM_H_

#include <Display/IViewingVolumeDecorator.h>
#include <Geometry/Plane.h>
#include <Scene/RenderNode.h>
#include <list>

namespace OpenEngine {
namespace Display {

using namespace OpenEngine::Geometry;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Renderers;
using std::list;

/**
 * Frustum viewing volume decorator.
 * Extends viewing volumes with clipping functionality.
 *
 * @class Frustum Frustum.h Display/Frustum.h
 */
class Frustum : public IViewingVolumeDecorator {
private:

    //! private render node structure to visualize the frustum.
    class FNode : public RenderNode {
    private:
        Frustum& frustum;
    public:
        explicit FNode(Frustum& frustum);
        ~FNode();
        FNode(FNode& node);
        ISceneNode* Clone();
        void Apply(IRenderingView* view);
    };

    Plane* planes[6];           //!< computed clipping planes.
    FNode* node;                //!< rendering node.
    Vector<3,float> center;     //!< center of frustum.
    Vector<3,float> frame[32];  //!< computed frame vectors.

    bool visualizeClipping;          //!< maintain visualizing clipping info
    list< Vector<3,float> > clipped; //!< clipped objects
    list< Vector<3,float> > visible; //!< visible objects

    // state change update methods
    void UpdatePlanes();
    //void UpdateFrame();
    
    float farClip;

public:

    // constructor / destructor
    Frustum(IViewingVolume& volume,
            const float farClip = 30000);
    virtual ~Frustum();

    // get / set methods
    virtual float GetFarClippingPlane();
    virtual void SetFarClippingPlane(const float farClip);

    // new frustum methods
    virtual RenderNode* GetFrustumNode();
    void VisualizeClipping(bool on);

    // overwritten viewing volume methods
    virtual void SignalRendering(const float dt);

    // viewing volume clipping methods
    virtual bool IsVisible(const Box& box);
};

} // NS Display
} // NS OpenEngine

#endif // _OE_FRUSTUM_H_
