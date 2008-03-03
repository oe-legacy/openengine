// Generic camera.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/Camera.h>
#include <Logging/Logger.h>
#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Display {

using namespace OpenEngine::Core;

/**
 * Create a camera decorator.
 *
 * @param volume Viewing volume to decorate.
 */
Camera::Camera(IViewingVolume& volume) : IViewingVolumeDecorator(volume) {

}

/**
 * Empty destructor.
 */
Camera::~Camera() {

}

/**
 * Move the camera relative to the current position.
 *
 * @param direction Relative direction to move the camera to
 */
void Camera::Move(const Vector<3,float> direction) {
    volume.SetPosition(volume.GetPosition() +
                       volume.GetDirection().RotateVector(direction));
}

/**
 * Move the camera relative to the current position.
 *
 * @param l Moves along the longitudinal axis (positive moves forward)
 * @param t Moves along the transverse axis (positive moves to the right)
 * @param v Moves along the vertical axis (positive moves upwards)
 */
void Camera::Move(const float l, const float t, const float v) {
    volume.SetPosition(volume.GetPosition() +
                       volume.GetDirection().RotateVector(Vector<3,float>(t,v,-l)));
}

/**
 * Look at point.
 *
 * @param point Point to look at.
 */
void Camera::LookAt(const Vector<3,float> point) {
    SetDirection(point - volume.GetPosition(), Vector<3,float>(0,1,0));
}

/**
 * Look at point.
 *
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param z Z coordinate.
 */
void Camera::LookAt(const float x, const float y, const float z) {
    LookAt(Vector<3,float>(x,y,z));
}

/**
 * Rotates the camera by Tait-Bryan angles.
 * The rotation is performed in the order yaw, pitch and then roll.
 *
 * @param roll Positive rolls clockwise around the longitudinal axis
 * @param pitch Positive pitches upwards around the transverse axis
 * @param yaw Positive values turn to the left around the vertical axis
 */
void Camera::Rotate(const float roll, const float pitch, const float yaw) {
    float z = -roll; // z is the longitudinal axis (follows the body)
    float x = pitch; // x is transverse axis (follows the wings)
    float y = yaw;   // y is the vertical axis (obvious)
    Quaternion<float> q(x, y, z);
    q.Normalize();
    volume.SetDirection(volume.GetDirection() * q);
}

/**
 * Rotate around an arbitrary axis.
 *
 * @todo could we skip normalizing here if the axis is a unit vector?
 *
 * @code
 * // rotate the camera 45 degrees around the x-axis
 * Rotate(PI/2, Vector<3,float>(1,0,0));
 * @endcode
 *
 * @param angle Angle to rotate.
 * @param axis Axis to rotate about.
 */
void Camera::Rotate(const float angle, const Vector<3,float> axis) {
    Quaternion<float> q(angle, axis);
    q.Normalize();
    Rotate(q);
}

/**
 * Rotate by a quaternion.
 * Rotations can preferably be done with Rotate(angle, axis) if the
 * rotation is not already represented by a quaternion.
 *
 * @code
 * // rotate the camera 45 degrees around the x-axis
 * Quaternion<float> q(PI/2, Vector<3,float>(1,0,0));
 * Camera->Rotate(q);
 * @endcode
 *
 * @param q Quaternion encoded rotation.
 */
void Camera::Rotate(const Quaternion<float> q) {
    if (!q.IsNormalized())
        throw InvalidArgument("Rotation quaternions must be normalized.");
    volume.SetDirection(q * volume.GetDirection());
}

// Note: if this method is not declared gcc will not allow calling the
// inherited IViewingVolumeDecorator::SetDirection(Quaternion<float>)
// method on a camera instance.
void Camera::SetDirection(const Quaternion<float> direction) {
    volume.SetDirection(direction);
}

/**
 * Set direction by vector.
 *
 * @param direction Direction vector.
 * @param up Up vector.
 */
void Camera::SetDirection(const Vector<3,float> direction, const Vector<3,float> up) {
    if (direction.IsZero() || up.IsZero()) {
        logger.warning << "Ignoring call to Camera::SetDirection with the zero vector." << logger.end;
        return;
    }
    Vector<3,float> z(-direction);
    z.Normalize();
    Vector<3,float> x = up % z;
    Vector<3,float> y = z % x;
    Matrix<3,3,float> m(x, y, z);
    Quaternion<float> q(m);
    volume.SetDirection(q.GetNormalize());
}

} //NS Display
} //NS OpenEngine
