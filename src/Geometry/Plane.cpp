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
    : normal(normal.GetNormalize())
    , distance(distance) {
    point = this->normal * this->distance;
}

/**
 * Plane constructor.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param pointOnPlane a point on the plane.
 */
Plane::Plane(Vector<3,float> normal, Vector<3,float> point)
    : point(point) {
    this->normal = normal.GetNormalize();
    this->distance = fabs(this->normal * point);
}

Plane::~Plane() {

}

/**
 * Set the plane values.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param distance Distance from origin.
 */
void Plane::Set(Vector<3,float> normal, float distance) {
    SetNormal(normal);
    SetDistance(distance);
}

/**
 * Set the plane values.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param distance A point on the plane.
 */
void Plane::Set(Vector<3,float> normal, Vector<3,float> point) {
    this->normal = normal.GetNormalize();
    this->distance = fabs(this->normal * point);
}

/**
 * Set the normal value.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 */
void Plane::SetNormal(Vector<3,float> normal) {
    this->normal = normal.GetNormalize();
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
    return distance;
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
    point = normal * distance;
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
    distance = fabs(normal * point);
}

/**
 * Get some point that lies on the plane.
 */
Vector<3,float> Plane::GetPointOnPlane() {
    return point;
}

} //NS Common
} //NS OpenEngine
