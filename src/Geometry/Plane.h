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
 * perpendicular to the plane or by a normal vector and the distance
 * from origin.
 *
 * The plane equation: Ax + By + Cz + D = 0
 *
 * @class Plane Plane.h Geometry/Plane.h
 */
class Plane {

friend class Tests;

private:
    Vector<3,float> normal;     //!< normal of the plane [A,B,C]
    float distance;             //!< distance from origin scaled by the length of the normal
    Vector<3,float> point;      //!< a point in the plane

public:

    Plane(Vector<3,float> normal, float distance);
    Plane(Vector<3,float> normal, Vector<3,float> point);
    virtual ~Plane();

    void Set(Vector<3,float> normal, float distance);
    void Set(Vector<3,float> normal, Vector<3,float> point);

    Vector<3,float> GetNormal() const;
    float GetDistance() const;
    Vector<3,float> GetPointOnPlane() const;

    std::string ToString() const {
        std::stringstream ss;
        ss << "(n=" << normal << ", p:" << point << ")";
        return ss.str();
    }
};

} //NS Common
} //NS OpenEngine

#endif // _GEOMETRY_PLANE_H_
