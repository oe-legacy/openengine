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
    , distance(distance) {
    this->point = Vector<3, float>(distance / normal[0], 0, 0);
}

/**
 * Plane constructor.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param point a point on the plane.
 */
Plane::Plane(Vector<3,float> normal, Vector<3,float> point)
    : normal(normal), 
      point(point) {
    distance = normal * point;
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
    this->normal = normal;
    this->distance = distance;
    point = Vector<3, float>(distance / normal[0], 0, 0);
}

/**
 * Set the plane values.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param point A point on the plane.
 */
void Plane::Set(Vector<3,float> normal, Vector<3,float> point) {
    this->normal = normal;
    this->point = point;
    distance = normal * point;
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
 * Get some point that lies on the plane.
 */
Vector<3,float> Plane::GetPointOnPlane() {
    return point;
}

} //NS Common
} //NS OpenEngine
