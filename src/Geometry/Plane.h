// Plane.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_PLANE_H_
#define _GEOMETRY_PLANE_H_

#include <Math/Vector.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * Plane.
 * A plane is defined by a point in the plane and a vector
 * perpendicular to the plane.
 *
 * The plane equation: Ax + By + Cz + D = 0
 *
 * @class Plane Plane.h Geometry/Plane.h
 */
class Plane {

friend class Tests;

private:
    Vector<3,float> normal;     //!< normal of the plane [A,B,C]
    float distance;             //!< distance from origin 
    Vector<3,float> point;
    bool distCached;
public:

    Plane(Vector<3,float> normal, float distance);
    Plane(Vector<3,float> normal, Vector<3,float> pointOnPlane);
    virtual ~Plane();

    Vector<3,float> GetNormal();
    void SetNormal(Vector<3,float> normal);

    float GetDistance();
    void SetDistance(float distance);

    void SetPointOnPlane(Vector<3,float> point);
    Vector<3,float> GetPointOnPlane();
     
    void Set(Vector<3,float> normal, float distance);

    void Normalize();
};

} //NS Common
} //NS OpenEngine

#endif // _GEOMETRY_PLANE_H_
