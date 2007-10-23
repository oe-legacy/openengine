// Sphere.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BOUNDING_SPHERE_H_
#define _BOUNDING_SPHERE_H_

#include <Geometry/FaceSet.h>
#include <Geometry/BoundingGeometry.h>
#include <string>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * Bounding geometry sphere.
 *
 * @class Sphere Sphere.h Geometry/Sphere.h
 */
class Sphere : public BoundingGeometry {

friend class Geometry;
    
private:
    Vector<3,float> center;
    float diameter;    

public:
    explicit Sphere();

    Sphere(Vector<3,float> center, float diameter);

    Sphere(FaceSet& faces);
    
    void Move(Vector<3,float> dir);

    float GetDiameter() const;
    float GetRadius() const;

    void SetRadius(const float r);

    Vector<3,float> GetCenter() const;

    void SetCenter(const Vector<3,float> center);
    
    bool Intersects(const Vector<3,float> point) const;

    bool Intersects(const Line line) const;

    bool Intersects(const Plane plane) const;

};

} //NS Common
} //NS OpenEngine

#endif
