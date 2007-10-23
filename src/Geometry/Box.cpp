// Box.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Box.h>
#include <Geometry/Face.h>
#include <Geometry/Line.h>
#include <Geometry/Plane.h>
#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Core::NotImplemented;
using OpenEngine::Math::Vector;

/**
 * Create a bounding box from a set of faces.
 * If the face set is empty the box will have center in [0,0,0] and
 * the corner will be [0,0,0].
 *
 * @param faces Face set to create a box from.
 */
Box::Box(FaceSet& faces) {
    if (faces.Size() == 0) return;

    // initialize max and min with the first member of the face set
    FaceList::iterator itr = faces.begin();
    Vector<3,float> max((*itr)->vert[0]);
    Vector<3,float> min(max);

    // find the boundary values
    for (; itr != faces.end(); itr++) {
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
    corner = max - center;
    // compute the corners
    float x = corner[0];
    float y = corner[1];
    float z = corner[2];
    SetCorner(1,1,1, center+Vector<3,float>( x, y, z));
    SetCorner(1,1,0, center+Vector<3,float>( x, y,-z));
    SetCorner(1,0,1, center+Vector<3,float>( x,-y, z));
    SetCorner(1,0,0, center+Vector<3,float>( x,-y,-z));
    SetCorner(0,1,1, center+Vector<3,float>(-x, y, z));
    SetCorner(0,1,0, center+Vector<3,float>(-x, y,-z));
    SetCorner(0,0,1, center+Vector<3,float>(-x,-y, z));
    SetCorner(0,0,0, center+Vector<3,float>(-x,-y,-z));
}

/**
 * Get the center of the box.
 *
 * @return Center of the box.
 */
Vector<3,float> Box::GetCenter() const {
    return center;
}

/**
 * Get the relative corner value.
 * The vector is from the center to the corner and all components have
 * a positive sign.
 *
 * @return Corner vector from center.
 */
Vector<3,float> Box::GetCorner() const {
    return corner;
}

/**
 * Set a corner by its signed index.
 *
 * A positive sign given with: true / 1.
 * A negative sign given with: false / 0.
 *
 * @param signX The sign of the x component relative to the center.
 * @param signY The sign of the y component relative to the center.
 * @param signZ The sign of the z component relative to the center.
 * @param corner The corner position (not relative to the center).
 */
void Box::SetCorner(const bool signX, const bool signY, const bool signZ, Vector<3,float> corner) {
    corners[ signX*1 + signY*2 + signZ*4 ] = corner;
}

/**
 * Get a corner by index.
 * The order of the corners is unspecified. The index range is 0 to 7.
 *
 * @param index The of the corner.
 * @return The absolute corner position given by the index.
 */
Vector<3,float> Box::GetCorner(const int index) const {
    return corners[ index ];
}

/**
 * Get a corner by its signed index.
 *
 * A positive sign given with: true / 1.
 * A negative sign given with: false / 0.
 *
 * @param signX The sign of the x component relative to the center.
 * @param signY The sign of the y component relative to the center.
 * @param signZ The sign of the z component relative to the center.
 * @return The absolute corner position given by the sign index.
 */
Vector<3,float> Box::GetCorner(const bool signX, const bool signY, const bool signZ) const {
    return corners[ signX*1 + signY*2 + signZ*4 ];
}

/**
 * Check if point is inside box.
 *
 * NOTE: NOT IMPLEMENTED YET!
 *
 * @param point point to test.
 * @return true if point is inside, false otherwise.
 */
bool Box::Intersects(const Vector<3,float> point) const {
    throw NotImplemented();
}

/**
 * Check if line intersects with the box.
 *
 * Based on RayAABBOverlap from Real Time Rendering Second Edition.
 *
 * @param line line to test.
 * @return true if part of, or the whole line is inside, false otherwise.
 */
bool Box::Intersects(const Line line) const {
    // The lines direction.
    Vector<3,float> dir = line.point1 - line.point2;
    // Midpoint of the line.
    Vector<3,float> mid = line.point1 + (dir / 2);
    // Half the length of the line segment.
    float hl = dir.GetLength() / 2;

    /* ALGORITHM: Use the separating axis
    theorem to see if the line segment
    and the box overlap. A line
    segment is a degenerate OBB. */

    //const VECTOR T = b.P - mid;
    Vector<3,float> t = center - mid;
    float r;

    //do any of the principal axes
    //form a separating axis?

    if( fabs(t[0]) > (corner.Get(0) + hl * fabs(dir[0]) ))
    return false;

    if( fabs(t[1]) > corner.Get(1) + hl*fabs(dir[1]) )
    return false;

    if( fabs(t[2]) > corner.Get(2) + hl*fabs(dir[2]) )
    return false;

    /* NOTE: Since the separating axis is
    perpendicular to the line in these
    last four cases, the line does not
    contribute to the projection. */

    //l.cross(x-axis)?

    r = corner.Get(1)*fabs(dir[2]) + corner.Get(2)*fabs(dir[1]);

    if( fabs(t[1]*dir[2] - t[2]*dir[1]) > r )
    return false;

    //l.cross(y-axis)?

    r = corner.Get(0)*fabs(dir[2]) + corner.Get(2)*fabs(dir[0]);

    if( fabs(t[2]*dir[0] - t[0]*dir[2]) > r )
    return false;

    //l.cross(z-axis)?

    r = corner.Get(0)*fabs(dir[1]) + corner.Get(1)*fabs(dir[0]);

    if( fabs(t[0]*dir[1] - t[1]*dir[0]) > r )
    return false;

    return true;
}

/**
 * Check if a plane intersects with the box.
 *
 * NOTE: NOT IMPLEMENTED YET!
 *
 * @param plane to test.
 * @return true if part of the plane is inside, false otherwise.
 */
bool Box::Intersects(const Plane plane) const {
    throw NotImplemented(); 
}

} //NS Geometry
} //NS OpenEngine
