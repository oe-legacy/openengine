// Generic camera.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Display/IViewingVolumeDecorator.h>

namespace OpenEngine {
namespace Display {

/**
 * Base camera.
 * Decorates(extends) a viewing volume with methods for rotating and
 * moving the camera.
 *
 * Camera usage:
 * @code
 * // create camera with an existing viewing volume.
 * cam = new Camera(*volume);
 *
 * // offset the camera position.
 * // this is given as (x,y,z) in the global axis system.
 * cam->SetPosition(0,2,5); // 5 up the z-axis = backwards a notch
 *                          // and 2 up the y-axis = up the vertical axis
 *
 * // set the direction to the origin (we will be looking slightly downwards)
 * cam->LookAt(Vector<3,float>(0,0,0));
 * @endcode
 *
 * @class Camera Camera.h Display/Camera.h
 */
class Camera : public IViewingVolumeDecorator {
public:

    Camera(IViewingVolume& volume);
    virtual ~Camera();

    // Extended viewing volume methods
    virtual void SetDirection(const Quaternion<float> direction);
    virtual void SetDirection(const Vector<3,float> dir, const Vector<3,float> up);
    
    // New camera methods
    virtual void Move(const Vector<3,float> position);
    virtual void Move(const float l, const float t, const float v);
    virtual void LookAt(const Vector<3,float> point);
    virtual void LookAt(const float x, const float y, const float z);
    virtual void Rotate(const float roll, const float pitch, const float yaw);
    virtual void Rotate(const float angle, const Vector<3,float> axis);
    virtual void Rotate(const Quaternion<float> rotation);
    
};

} // NS Display
} // NS OpenEngine

#endif // _CAMERA_H_
