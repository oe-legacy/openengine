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
     * Get the projection matrix of the viewing volume.
     *
     * @return Projection matrix of viewing volume.
     */
    virtual Matrix<4,4,float> GetProjectionMatrix() = 0;

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
     * Update the projection with respect to the window dimensions
     *
     * @param width the width
     * @param height the height
     */
    virtual void Update(const unsigned int width, const unsigned int height) = 0;
    
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_VIEWING_VOLUME_H_
