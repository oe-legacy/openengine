// Bounding geometry.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BOUNDING_GEOMETRY_H_
#define _BOUNDING_GEOMETRY_H_

#include <Geometry/Tests.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Geometry {

// forward declarations
class FaceSet;
class Line;
class Plane;

using OpenEngine::Math::Vector;

/**
 * Bounding geometric shape.
 *
 * @class BoundingGeometry BoundingGeometry.h Geometry/BoundingGeometry.h
 */
class BoundingGeometry {
public:

    /**
     * Default destructor.
     */
    virtual ~BoundingGeometry() {};

    /**
     * Test if point is in the bounding geometry.
     *
     * @param point Vector representation of point
     * @return True if inside bounds false if outside
     */
    virtual bool Intersects(const Vector<3,float> point) const = 0;

    /**
     * Test if line intersects with the bounding geometry.
     *
     * @param line Line to test
     * @return True if the line is inside at some point, false otherwise
     */
    virtual bool Intersects(const Line line) const = 0;

    /**
     * Test if plane intersects with the bounding geometry.
     *
     * @param plane Plane to test
     * @return True if the plane is inside at some point, false otherwise
     */
    virtual bool Intersects(const Plane plane) const = 0;

};

} // NS Geometry
} // NS OpenEngine

#endif
