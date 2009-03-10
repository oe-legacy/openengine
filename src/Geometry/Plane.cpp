// Plane.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Plane.h>

#include <Core/Exceptions.h>
namespace OpenEngine {
namespace Geometry {

using Core::NotImplemented;

/**
 * Plane constructor.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param distance Distance from origin.
 */
Plane::Plane(Vector<3,float> normal, float distance) 
    : normal(normal)
    , point(normal.GetNormalize()*distance)
    , distCached(true) {}

// }

/**
 * Plane constructor.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param pointOnPlane a point on the plane.
 */
Plane::Plane(Vector<3,float> normal, Vector<3,float> pointOnPlane) 
    : normal(normal)
    , point(pointOnPlane)
    , distCached(false) {}

Plane::~Plane() {
}

/**
 * Set the plane values.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param distance Distance from origin.
 */
void Plane::Set(Vector<3,float> normal, float distance) {
    this->normal = normal;
    this->distance = distance;
    this->distCached = true;
}

/**
 * Set the normal value.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 */
void Plane::SetNormal(Vector<3,float> normal) {
    this->normal = normal;
}

/**
 * Get the normal value.
 */
Vector<3,float> Plane::GetNormal() {
    return normal;
}

/**
 * Get the shortest distance to the origin.
 *
 * @todo This only works if plane has been initialized with distance
 * or a call to SetDistance has been made. Implement conversion from 
 * some point on plane to distance.
 */
float Plane::GetDistance() {
    if (distCached) return distance;
    throw NotImplemented("Plane conversion from point on plane to distance from origin");
}

/**
 * Set the distance to the origin.
 *
 * This overrides any call to SetPointOnPlane.
 *
 * @param distance The distance to the origin 
 */
void Plane::SetDistance(float distance) {
    this->distance = distance;
    this->distCached = true;
    this->point = normal.GetNormalize()*distance;
}

/**
 * Set a point on the plane.
 *
 * This overrides any call to SetDistance.
 *
 * @param distance The distance to the origin 
 */
void Plane::SetPointOnPlane(Vector<3,float> point) {
    this->point = point;
    this->distCached = false;
}

/**
 * Get some point that lies on the plane.
 */
Vector<3,float> Plane::GetPointOnPlane() {
    return point;
}

/**
 * Normalize the normal vector.
 */
void Plane::Normalize() {
    normal.Normalize();
} 

} //NS Common
} //NS OpenEngine
