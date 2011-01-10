// Follow camera.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TRACKING_CAMERA_H_
#define _TRACKING_CAMERA_H_

#include <Display/Camera.h>

namespace OpenEngine {

// forward declarations
namespace Scene { class TransformationNode; }

namespace Display {

using OpenEngine::Scene::TransformationNode;

/**
 * Follow camera.
 * The follow camera can be bound to a transformation node that it
 * will "follow". The result is that the cameras origin will be placed
 * at the position of the transformation and all modification methods
 * will be relative to that point.
 *
 * If no transformation node is attached the camera will "follow" the
 * absolute origin and therefor function exactly as an ordinary
 * camera.
 *
 * TrackingCamera usage:
 * @code
 * // create camera with an existing viewing volume.
 * cam = new TrackingCamera(*volume);
 *
 * // attach to a transformation node
 * cam->Follow(myTranNode);
 *
 * // offset the camera position
 * // this is given as (x,y,z) in the transformation nodes local axis
 * // system. 
 * cam->SetPosition(0,2,5);
 *
 * // set the direction to the origin (center of what is under the
 * // transformation node)
 * cam->LookAt(Vector<3,float>(0,0,0));
 * @endcode
 *
 * @class TrackingCamera TrackingCamera.h Display/TrackingCamera.h
 */
class TrackingCamera : public Camera {

private:
    //! Transformation node to track.
    TransformationNode* track;

    //! Transformation relative to the transformation node.
    Camera* local;

public:

    // Mandatory constructors and destructor.
    TrackingCamera(IViewingVolume& volume);
    virtual ~TrackingCamera();

    // Overwritten camera methods
    virtual void SetDirection(const Vector<3,float> dir, const Vector<3,float> up);
    virtual void Move(const float l, const float t, const float v);
    virtual void LookAt(const Vector<3,float> point);
    virtual void LookAt(const float x, const float y, const float z);
    virtual void Rotate(const float roll, const float pitch, const float yaw);
    virtual void Rotate(const float angle, const Vector<3,float> axis);
    virtual void Rotate(const Quaternion<float> rotation);

    // Overwritten viewing volume methods
    virtual void SetPosition(const Vector<3,float> position);
    virtual void SetDirection(const Quaternion<float> direction);
    virtual void SignalRendering(const float dt);

    // New tracking cam methods
    virtual void Track(TransformationNode* node);

};

} // NS Display
} // NS OpenEngine

#endif // _TRACKING_CAMERA_H_
