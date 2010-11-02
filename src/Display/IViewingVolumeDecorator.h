// Interface for viewing volume decorators.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_VIEWING_VOLUME_DECORATOR_H_
#define _INTERFACE_VIEWING_VOLUME_DECORATOR_H_

#include <Display/IViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * Viewing volume decorator interface.
 *
 * @class IViewingVolumeDecorator IViewingVolumeDecorator.h Display/IViewingVolumeDecorator.h
 */
class IViewingVolumeDecorator : public IViewingVolume {
protected:

    //! Decorated viewing volume
    IViewingVolume& volume;

public:
    
    /**
     * Decorator constructor.
     *
     * @param volume Viewing volume to decorate.
     */
    IViewingVolumeDecorator(IViewingVolume& volume) : volume(volume) {}

    /**
     * Decorator destructor.
     */
    virtual ~IViewingVolumeDecorator() {}

    virtual void Update(const unsigned int width, const unsigned int height) {
        volume.Update(width, height);
    }

    /**
     * Set viewing volume position.
     * Defaults to setting the position on the decorated viewing
     * volume.
     *
     * @param position Position in space.
     */
    virtual void SetPosition(const Vector<3,float> position) {
        volume.SetPosition(position);
    }

    /**
     * Set viewing volume direction.
     * Defaults to setting the direction on the decorated viewing
     * volume.
     *
     * @param direction Direction quaternion.
     */
    virtual void SetDirection(const Quaternion<float> direction) {
        volume.SetDirection(direction);
    }

    /**
     * Get viewing volume position.
     * Defaults to getting the position from the decorated viewing
     * volume.
     *
     * @return Position vector
     */
    virtual Vector<3,float> GetPosition() {
        return volume.GetPosition();
    }

    /**
     * Get viewing volume direction.
     * Defaults to getting the direction from the decorated viewing
     * volume.
     *
     * @return Direction vector
     */
    virtual Quaternion<float> GetDirection() {
        return volume.GetDirection();
    }

    /**
     * Get the view matrix of the viewing volume.
     * Defaults to getting the view matrix from the decorated viewing
     * volume.
     *
     * @return View matrix of viewing volume.
     */
    virtual Matrix<4,4,float> GetViewMatrix() {
        return volume.GetViewMatrix();
    }
    
    /**
     * Signal rendering start.
     * Defaults to calling the signal method on the decorated viewing
     * volume.
     */
    virtual void SignalRendering(const float dt) {
        volume.SignalRendering(dt);
    }

    /**
     * Test if a square is visible.
     * Defaults to performing the test on the decorated viewing
     * volume.
     *
     * @param square Bounding square.
     * @return True if part of the square is visible.
     */
    virtual bool IsVisible(const Square& square) {
        return volume.IsVisible(square);
    }

    /**
     * Test if a sphere is visible.
     * Defaults to performing the test on the decorated viewing
     * volume.
     *
     * @param sphere Bounding sphere.
     * @return True if part of the sphere is visible.
     */
    virtual bool IsVisible(const Sphere& sphere) {
        return volume.IsVisible(sphere);
    }

    /**
     * Test if a box is visible.
     * Defaults to performing the test on the decorated viewing
     * volume.
     *
     * @param box Bounding box.
     * @return True if part of the box is visible.
     */
    virtual bool IsVisible(const Box& box) {
        return volume.IsVisible(box);
    }
    
    virtual Matrix<4,4,float> GetProjectionMatrix() {
    	return volume.GetProjectionMatrix();
    }

};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_VIEWING_VOLUME_DECORATOR_H_
