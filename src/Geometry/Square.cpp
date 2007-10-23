// Square.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Square.h>
#include <Geometry/Face.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Line.h>
#include <Geometry/Plane.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Geometry {

/**
 * Create a square from a set of faces.
 * The square will be quadratic and span a section of the y-plan
 * thereby containing all faces in there x and z positions.
 * If the face set is empty the square will have center in 0,0 and a
 * size of 0.
 *
 * @param faces Face set to calculate volume from.
 */
Square::Square(FaceSet& faces) : hsize(0) {
    if (faces.Size() == 0) return;

    // initialize max and min with the x-z coordinates of the first
    // vertex in the first face.
    FaceList::iterator itr = faces.begin();
    Vector<2,float> max((*itr)->vert[0][0], (*itr)->vert[0][2]);
    Vector<2,float> min(max);

    // find the boundary values
    for (; itr != faces.end(); itr++) {
        for (int i=0; i<3; i++) {
            Vector<3,float> v = (*itr)->vert[i];
            if (v[0] > max[0]) max[0] = v[0];
            if (v[0] < min[0]) min[0] = v[0];
            if (v[2] > max[1]) max[1] = v[2];
            if (v[2] < min[1]) min[1] = v[2];
        }   
    }
    
    // compute the center and half size values
    center = ((max - min) / 2) + min;
    hsize = fabs((max - min).Max() / 2);

    CalculateSides();
}

/**
 * Copy constructor.
 *
 * @param square Square to copy.
 */
Square::Square(const Square& square){
    this->center = square.center;
    this->hsize = square.hsize;
    CalculateSides();
}

/**
 * Create square with a volume.
 *
 * @param center Center of the square.
 * @param size Size of the square sides.
 */
Square::Square(Vector<2,float> center, float size) {
    this->center = center;
    this->hsize = size / 2.0f;
    CalculateSides();
}

/**
 * Square destructor.
 * Deletes all internally held lines defining the square sides.
 */
Square::~Square() {
    sides.empty();
}

/**
 * Get the size of the square sides.
 *
 * @return Length of sides.
 */
float Square::GetSize() const {
    return hsize * 2;
}

/**
 * Get half the size of the square sides.
 *
 * @return Half length of sides.
 */
float Square::GetHalfSize() const {
    return hsize;
}

/**
 * Get the square center.
 *
 * @return Center of the square.
 */
Vector<2,float> Square::GetCenter() const {
    return center;
}

/**
 * Test if point is contained in the square.
 *
 * @param point Point to test for containment.
 * @return True if contained.
 */
bool Square::Intersects(const Vector<3,float> point) const {
    float x, z;
    x = point.Get(0) - center.Get(0);
    z = point.Get(2) - center.Get(1);
    return (fabs(x) <= hsize &&
            fabs(z) <= hsize);
}

/**
 * Test if a line intersects with the square.
 * This is also true if the hole line is contained within the square.
 *
 * @param line Line to test for intersection.
 * @return True if intersecting.
 */
bool Square::Intersects(const Line line) const {
    // test end points
    if (this->Intersects(line.point1) ||
        this->Intersects(line.point2))
        return true;
    // project the line to the x-z plane
    Line l(line);
    l.point1[1] = 0;
    l.point2[1] = 0;
    for (unsigned int i=0; i<sides.size(); i++)
        if (sides[i]->Intersects(l))
            return true;
    return false;
}

/**
 * Test if a plane intersects with the square.
 *
 * @todo This function is not implemented.
 *
 * @param plane Plane to test for intersection.
 * @return True if intersecting.
 */
bool Square::Intersects(const Plane plane) const {
    throw Core::NotImplemented("Square::Intersects(Plane) is not implemented.");
}

/**
 * Calculate the square sided.
 */
void Square::CalculateSides() {
    Vector<3, float> min(center[0]-hsize, 0, center[1]-hsize);
    Vector<3, float> max(center[0]+hsize, 0, center[1]+hsize);

    Vector<3, float> p1(center[0]-hsize, 0, center[1]+hsize);
    Vector<3, float> p2(center[0]+hsize, 0, center[1]-hsize);
    
    sides.push_back( new Line(min, p1) );
    sides.push_back( new Line(min, p2) );
    sides.push_back( new Line(p1, max) );
    sides.push_back( new Line(p2, max) );
}

} // NS Geometry
} // NS OpenEngine
