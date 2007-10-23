// Geometry subsystem.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <Math/Vector.h>

namespace OpenEngine {

/**
 * Geometry subsystem.
 *
 * @namespace OpenEngine::Geometry
 */

namespace Geometry {

// forward declarations
class Square;
class Box;
class Sphere;

using OpenEngine::Math::Vector;

/**
 * Geometric shape.
 *
 * @class Geometry Geometry.h Geometry/Geometry.h
 */
class Geometry {
public:
    Geometry();
    virtual ~Geometry();

    /**
     * Check if square and box intersects with each other.
     *
     * @param square to test.
     * @param box to test.
     * @return true if the square and box intersect, false otherwise.
     */
    static bool Intersects(const Square& square, const Box& box);

    /**
     * Same as Square and box test, just for convenience.  
     *
     * @param square to test.
     * @param box to test.
     * @return true if the square and box intersect, false otherwise.
     *
     * @see Intersects(Square, Box)
     */
    static inline bool Intersects(const Box& box, const Square& square);


    /**
     * Check if square and box intersects with each other.
     *
     * @param square to test.
     * @param sphere to test.
     * @return true if the square and sphere intersect, false otherwise.
     */
    static bool Intersects(const Square& square, const Sphere& sphere);

    /**
     * Same as Square and sphere test, just for convenience.  
     *
     * @param square to test.
     * @param sphere to test.
     * @return true if the square and sphere intersect, false otherwise.
     *
     * @see Intersects(Square, Sphere)
     */
    static inline bool Intersects(const Sphere& sphere, const Square& square);

};

} // NS Geometry
} // NS OpenEngine

#endif // _GEOMETRY_H_
