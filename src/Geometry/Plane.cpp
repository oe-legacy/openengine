// Plane.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Plane.h>
#include <Geometry/Line.h>

namespace OpenEngine {
namespace Geometry {

/**
 * Plane constructor.
 *
 * @param normal Vector that is orthogonal (perpendicular) to the plane.
 * @param distance Distance from origin.
 */
Plane::Plane(Vector<3,float> normal, float distance) 
    : normal(normal),
      distance(distance) { 

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
}

/**
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/planeplane/
 */
Line Plane::Intersection(Plane p) {
    // compute normal for intersection
    Vector<3,float> n = normal % p.normal;
    
    float s1  = normal * normal;
    float s2  = p.normal * p.normal;
    float s12 = normal * p.normal;
    float d   = s1 * s2 - s12 * s12;
    float c1  = (distance * s2 - p.distance * s12) / d;
    float c2  = (p.distance * s1 - distance * s12) / d;

    Vector<3,float> point(c1 * normal + c2 * p.normal);
    return Line(point, point + n * 100);
}

} //NS Common
} //NS OpenEngine
