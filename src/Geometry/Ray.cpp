// Ray.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Ray.h>

namespace OpenEngine {
namespace Geometry {

/**
 * Ray constructor.
 *
 * @param point Point on ray.
 * @param direction Ray direction.
 */
Ray::Ray(Vector<3,float> point, Vector<3,float> direction) 
    : point(point)
    , dir(direction) {

}

/**
 * Default destructor
 */
Ray::~Ray() {

}

void Ray::SetPoint(Vector<3,float> point) {
    this->point = point;
}

void Ray::SetDirection(Vector<3,float> direction) {
    this->dir = direction;
}

Vector<3,float> Ray::GetPoint() {
    return point;
}

Vector<3,float> Ray::GetDirection() {
    return dir;
}



} //NS Geometry
} //NS OpenEngine
