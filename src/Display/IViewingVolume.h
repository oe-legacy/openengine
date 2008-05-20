// Interface for viewing volume.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_VIEWING_VOLUME_H_
#define _INTERFACE_VIEWING_VOLUME_H_

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>

#include <Geometry/Square.h>
#include <Geometry/Sphere.h>
#include <Geometry/Box.h>

namespace OpenEngine {
namespace Display {

using namespace OpenEngine::Math;
using namespace OpenEngine::Geometry;

/**
 * Viewing volume interface.
 * A viewing volume is a structure that describes a view in 3d
 * space. It contains information on location and direction plus means
 * of testing if a bounding structure is visible in the viewing
 * volume.
 *
 * @class IViewingVolume IViewingVolume.h Display/IViewingVolume.h
 */
class IViewingVolume {
public:
    enum ProjectionMode { OE_PERSPECTIVE, OE_ORTHOGONAL };

protected:
    float fov;                  //!< field of view.
    float aspect;               //!< aspect ratio.

    // We would have liked to use near/far here but VC++ has defined
    // near and far so we don't use them.
    float distNear;             //!< near clipping distance.
    float distFar;              //!< far clipping distance.

    ProjectionMode projectionMode;

public:
    /**
     * Default constructor.
     */
    IViewingVolume() : projectionMode(OE_PERSPECTIVE) {}

    /**
     * Module destructor.
     */
    virtual ~IViewingVolume() {}

    /**
     * Set viewing volume position.
     *
     * @param position Position in space
     */
    virtual void SetPosition(const Vector<3,float> position) = 0;

    /**
     * Set viewing volume direction.
     *
     * @param direction Direction quaternion.
     */
    virtual void SetDirection(const Quaternion<float> direction) = 0;

    /**
     * Get viewing volume position.
     *
     * @return Position vector
     */
    virtual Vector<3,float> GetPosition() = 0;

    /**
     * Get viewing volume direction.
     *
     * @return Direction vector
     */
    virtual Quaternion<float> GetDirection() = 0;

    /**
     * Get the view matrix of the viewing volume.
     * The resulting rotation matrix is in row major order.
     *
     * @return View matrix of viewing volume.
     */
    virtual Matrix<4,4,float> GetViewMatrix() = 0;

    /**
     * Signal method called before rendering run.
     * Can be used to update the viewing volume state before the
     * renderer starts rendering.
     */
    virtual void SignalRendering(const float dt) = 0;

    /**
     * Test if a square is visible.
     *
     * @param square Bounding square.
     * @return True if part of the square is visible.
     */
    virtual bool IsVisible(const Square& square) = 0;

    /**
     * Test if a sphere is visible.
     *
     * @param sphere Bounding sphere.
     * @return True if part of the sphere is visible.
     */
    virtual bool IsVisible(const Sphere& sphere) = 0;

    /**
     * Test if a box is visible.
     *
     * @param box Bounding box.
     * @return True if part of the box is visible.
     */
    virtual bool IsVisible(const Box& box) = 0;

    /**
     * Set the field of view.
     *
     * @param fov Field of view.
     */
    virtual void SetFOV(const float fov) = 0;

    /**
     * Get the current field of view.
     *
     * @return Field of view.
     */
    virtual float GetFOV() = 0;

    /**
     * Set the aspect ratio.
     *
     * @param aspect Aspect ratio.
     */
    virtual void SetAspect(const float aspect) = 0;

    /**
     * Get the current aspect ratio.
     */
    virtual float GetAspect() = 0;

    /**
     * Set the distance to the near clipping plane.
     *
     * @param distNear Near clipping plane.
     */
    virtual void SetNear(const float distNear) = 0;

    /**
     * Get the current distance to the near clipping plane.
     *
     * @return Near clipping plane.
     */
    virtual float GetNear() = 0;

    /**
     * Set the distance to the far clipping plane.
     *
     * @param distFar Far clipping plane.
     */
    virtual void SetFar(const float distFar) = 0;

    /**
     * Get the current distance to the far clipping plane.
     *
     * @return Far clipping plane.
     */
    virtual float GetFar() = 0;

    /**
     * Set the projection mode for the volume.
     *
     * @param projectionMode projection mode.
     */
    virtual void SetProjectionMode(ProjectionMode projectionMode) = 0;

    /**
     * Get the projection mode for the volume.
     *
     * @return projection mode.
     */
    virtual ProjectionMode GetProjectionMode() = 0;
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_VIEWING_VOLUME_H_
