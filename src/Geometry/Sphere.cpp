// Sphere.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Sphere.h>
#include <Geometry/Face.h>
#include <Geometry/Line.h>
#include <Geometry/Plane.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * Create a sphere with center in [0,0,0] and diameter 0;
 */
Sphere::Sphere() : diameter(0) {

}

/**
 * Create a positioned sphere with a volume.
 *
 * @param center Center of sphere.
 * @param diameter Diameter of sphere.
 */
Sphere::Sphere(Vector<3,float> center, float diameter) 
    : center(center), diameter(diameter) {

}

/**
 * Create a sphere with a volume defined by a set of faces.
 *
 * @param faces Face set to calculate volume from.
 */
Sphere::Sphere(FaceSet& faces) {
    Vector<3,float> max, min;
    FaceList::iterator itr;
    for (itr = faces.begin(); itr != faces.end(); itr++) {
        for (int i=0; i<3; i++) {
            Vector<3,float> v = (*itr)->vert[i];
            for (int j=0; j<3; j++)
                if (v[j] < min[j]) min[j] = v[j];
                else if (v[j] > max[j]) max[j] = v[j];
        }
    }
    // set box center
    center = (max - min) / 2 + min;
    // set corner vector
    Vector<3,float> corner = max - center;

    if (corner.IsZero())
        throw Exception("Invalid volume -  radius of the sphere was zero");
    else
        diameter = corner.GetLength() / 2.0f;
}

/**
 * Move the sphere.
 *
 * @param dir Direction vector to move by.
 */
void Sphere::Move(Vector<3,float> dir) {
    this->center += dir;
}

/**
 * Set sphere center.
 *
 * @param center Sphere center.
 */
void Sphere::SetCenter(const Vector<3,float> center) {
    this->center = center;
}

/**
 * Get sphere center.
 *
 * @return Sphere center.
 */
Vector<3,float> Sphere::GetCenter() const {
    return center;
}

/**
 * Get sphere diameter.
 *
 * @return Sphere diameter.
 */
float Sphere::GetDiameter() const {
    return diameter;
}

/**
 * Get sphere radius.
 *
 * @return Sphere radius.
 */
float Sphere::GetRadius() const {
    return diameter/2.0;
}

/**
 * Set sphere radius.
 *
 * @param r Sphere radius.
 */
void Sphere::SetRadius(const float r) {
    diameter = r * 2;
}

/**
 * Test if sphere contains a point.
 *
 * @todo Not implemented.
 *
 * @param point Point to test for containment.
 */
bool Sphere::Intersects(const Vector<3,float> point) const { return false; }

/**
 * Test if sphere intersects with a line.
 *
 * @todo Not implemented.
 *
 * @param line Line to test for intersection.
 */
bool Sphere::Intersects(const Line line) const { return false; }

/**
 * Test if sphere intersects with a plane.
 *
 * @todo Not implemented.
 *
 * @param plane Plane to test for intersection.
 */
bool Sphere::Intersects(const Plane plane) const { return false; }

} //NS Geometry
} //NS OpenEngine
