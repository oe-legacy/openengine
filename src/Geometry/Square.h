// Square.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_SQUARE_H_
#define _GEOMETRY_SQUARE_H_

#include <Geometry/Sphere.h>
#include <Math/Vector.h>
#include <list>
#include <vector>
#include <string>

namespace OpenEngine {
namespace Geometry {

//forward declarations
class Line;

using OpenEngine::Math::Vector;
using std::list;
using std::vector;

/**
 * Bounding geometry square (2 dimensions).
 * Defines a (quadratic) square section of the x,z plane.
 *
 * @class Square Square.h Geometry/Square.h
 */
class Square {

friend class Tests;

private:
    float hsize;              //!< Half size
    Vector<2,float> center;   //!< Square center
    vector<Line*> sides; // used to cache side lines

    void CalculateSides();

public:
    explicit Square(FaceSet& faces);
    Square(const Square& square);
    Square(Vector<2,float> center, float size);
    ~Square();

    float GetSize() const;
    float GetHalfSize() const;
    Vector<2,float> GetCenter() const;
};

} //NS Common
} //NS OpenEngine

#endif
