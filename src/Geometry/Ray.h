// Ray.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_RAY_H_
#define _GEOMETRY_RAY_H_

#include <Math/Vector.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * Ray.  
 * Represented by a point and a direction vector. This is
 * identical to an infinite line in mathematics. For a
 * finite line segment see Line.h
 *
 * @see Line 
 * @class Ray Ray.h Geometry/Ray.h
 */
class Ray {

friend class Tests;

private:
    Vector<3,float> point;   //!< point on line
    Vector<3,float> dir;     //!< direction of line

public:
    
    Ray(Vector<3,float> point, Vector<3,float> direction);
    ~Ray();

    Vector<3,float> GetPoint();
    Vector<3,float> GetDirection();

    void SetPoint(Vector<3,float> point);
    void SetDirection(Vector<3,float> direction);
};

} //NS Geometry
} //NS OpenEngine

#endif // _GEOMETRY_RAY_H_
