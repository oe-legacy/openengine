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

} //NS Common
} //NS OpenEngine
