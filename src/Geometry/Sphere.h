// Sphere.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_SPHERE_H_
#define _GEOMETRY_SPHERE_H_

#include <Geometry/FaceSet.h>
#include <string>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * geometry sphere.
 *
 * @class Sphere Sphere.h Geometry/Sphere.h
 */
class Sphere {

friend class Tests;
    
private:
    Vector<3,float> center;
    float diameter;    

public:
    explicit Sphere();

    Sphere(float diameter);

    Sphere(Vector<3,float> center, float diameter);

    Sphere(FaceSet& faces);
    
    void Move(Vector<3,float> dir);

    float GetDiameter() const;
    float GetRadius() const;

    void SetRadius(const float r);

    Vector<3,float> GetCenter() const;

    void SetCenter(const Vector<3,float> center);
    
};

} //NS Common
} //NS OpenEngine

#endif
