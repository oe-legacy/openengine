// Concrete viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/ViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * Construct viewing volume.
 * Default position is origin (0,0,0) and direction is the
 * identity which should amount to looking along the negative
 * z-axis with the y-axis as up.
 */
ViewingVolume::ViewingVolume() :
    projectionMode(OE_PERSPECTIVE),
    distNear(10),
    distFar(300),
    aspect(4.0/3.0),
    fov(PI/4.0) {

}

/**
 * Empty destructor.
 */
ViewingVolume::~ViewingVolume() {

}

void ViewingVolume::SetPosition(const Vector<3,float> position) {
    this->position = position;
}

void ViewingVolume::SetDirection(const Quaternion<float> direction) {
    this->direction = direction;
}

Vector<3,float> ViewingVolume::GetPosition() {
    return position;
}

Quaternion<float> ViewingVolume::GetDirection() {
    return direction;
}

Matrix<4,4,float> ViewingVolume::GetViewMatrix() {
    // get the rotation from the quaternion and expand it
    Matrix<4,4,float> m = direction.GetMatrix().GetExpanded();
    Matrix<4,4,float> t;
    // write the position information
    t(3,0) = -position.Get(0);
    t(3,1) = -position.Get(1);
    t(3,2) = -position.Get(2);
    return t * m;
}

void ViewingVolume::SetFOV(const float fov) {
   this->fov = fov;
}

float ViewingVolume::GetFOV() {
   return fov;
}

void ViewingVolume::SetAspect(const float aspect) {
   this->aspect = aspect;
}

float ViewingVolume::GetAspect() {
   return aspect;
}

void ViewingVolume::SetNear(const float distNear) {
   this->distNear = distNear;
}

float ViewingVolume::GetNear() {
   return distNear;
}

void ViewingVolume::SetFar(const float distFar) {
   this->distFar = distFar;
}

float ViewingVolume::GetFar() {
   return distFar;
}

void ViewingVolume::SetProjectionMode(IViewingVolume::ProjectionMode projectionMode) {
   this->projectionMode = projectionMode;
}

IViewingVolume::ProjectionMode ViewingVolume::GetProjectionMode() {
   return projectionMode;
}

/**
 * Empty signal handler.
 */
void ViewingVolume::SignalRendering(const float dt) {

}

bool ViewingVolume::IsVisible(const Square& square) {
    return true;
}

bool ViewingVolume::IsVisible(const Sphere& sphere) {
    return true;
}

bool ViewingVolume::IsVisible(const Box& box) {
    return true;
}

} // NS Display
} // NS OpenEngine
