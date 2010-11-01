// Geometry subsystem.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Tests.h>

#include <Geometry/Square.h>
#include <Geometry/Box.h>
#include <Geometry/Sphere.h>
#include <Geometry/Line.h>
#include <Geometry/Plane.h>
#include <Geometry/Ray.h>
#include <Geometry/Polygon.h>

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Core::NotImplemented;

Tests::Tests() {}

Tests::~Tests() {}


bool Tests::Intersects(const Box& box1, const Box& box2) {
    throw NotImplemented();
}

bool Tests::Intersects(const Sphere& sphere1, const Sphere& sphere2) {
    throw NotImplemented();
}

bool Tests::Intersects(const Square& square1, const Square& square2) {
    throw NotImplemented();
}

bool Tests::Intersects(const Plane& plane1, const Plane& plane2) {
    throw NotImplemented();
}

/**
 * Check if a line intersects with another line
 *
 * @todo We should add an epsilon value to this test.
 *
 * @param line1 first Line to test intersection with.
 * @param line2 second Line to test intersection with.
 * @return True if the lines intersects.
 */
bool Tests::Intersects(const Line& line1, const Line& line2) {
    float distance = line1.Distance(line2);
    if (distance == 0)
        return true;
    return false;
}

bool Tests::Intersects(const Ray& ray1, const Ray& ray2) {
    throw NotImplemented();
}


/**
 * Check if point is inside box.
 *
 * @param point point to test.
 * @param box   box to test.
 * @return true if point is inside, false otherwise.
 */
bool Tests::Intersects(const Box& box, const Vector<3,float> point) {
    Vector<3,float> lowCorner,highCorner;

    lowCorner  = box.GetCorner(false,false,false);
    highCorner = box.GetCorner(true,true,true);

    

    if (point.Get(0) >= lowCorner.Get(0) &&
        point.Get(1) >= lowCorner.Get(1) &&
        point.Get(2) >= lowCorner.Get(2) &&
        point.Get(0) <= highCorner.Get(0) &&
        point.Get(1) <= highCorner.Get(1) &&
        point.Get(2) <= highCorner.Get(2))
        return true;
    else 
        return false;
}

bool Tests::Intersects(const Box& box, const Sphere& sphere) {
    throw NotImplemented();
}

bool Tests::Intersects(const Box& box, const Square& square) {
    return (Intersects(square, box.center + box.corner) ||
            Intersects(square, box.center + box.corner * Vector<3,float>( 1, 1,-1)) ||
            Intersects(square, box.center + box.corner * Vector<3,float>( 1,-1, 1)) ||
            Intersects(square, box.center + box.corner * Vector<3,float>( 1,-1,-1)) ||
            Intersects(square, box.center + box.corner * Vector<3,float>(-1, 1, 1)) ||
            Intersects(square, box.center + box.corner * Vector<3,float>(-1, 1,-1)) ||
            Intersects(square, box.center + box.corner * Vector<3,float>(-1,-1, 1)) ||
            Intersects(square, box.center + box.corner * Vector<3,float>(-1,-1,-1)) );
}

bool Tests::Intersects(const Box& box, const Plane& plane, Polygon* output) {
    Polygon polygon;
    // for each line connecting to points in the box
    std::vector<Line> lines = box.GetBoundingLines();
    for (unsigned int l=0; l<12; l++) {
        float i;
        Line line = lines[l];
        if ( Tests::Intersects(plane, line, &i) ) {
            Vector<3,float> point = (1-i) * line.point1 + i * line.point2;
            polygon.AddPoint(point);
        }
    }
    if (polygon.NumberOfPoints() < 3)
        return false;

    *output = polygon; 
    return true;
}

/**
 * Check if line intersects with the box.
 *
 * Based on RayAABBOverlap from Real Time Rendering Second Edition.
 *
 * @param box box to test.
 * @param line line to test.
 * @return true if part of, or the whole line is inside, false otherwise.
 */
bool Tests::Intersects(const Box& box, const Line& line) {
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
    Vector<3,float> t = box.center - mid;
    float r;

    //do any of the principal axes
    //form a separating axis?

    if( fabs(t[0]) > (box.corner.Get(0) + hl * fabs(dir[0]) ))
    return false;

    if( fabs(t[1]) > box.corner.Get(1) + hl*fabs(dir[1]) )
    return false;

    if( fabs(t[2]) > box.corner.Get(2) + hl*fabs(dir[2]) )
    return false;

    /* NOTE: Since the separating axis is
    perpendicular to the line in these
    last four cases, the line does not
    contribute to the projection. */

    //l.cross(x-axis)?

    r = box.corner.Get(1)*fabs(dir[2]) + box.corner.Get(2)*fabs(dir[1]);

    if( fabs(t[1]*dir[2] - t[2]*dir[1]) > r )
    return false;

    //l.cross(y-axis)?

    r = box.corner.Get(0)*fabs(dir[2]) + box.corner.Get(2)*fabs(dir[0]);

    if( fabs(t[2]*dir[0] - t[0]*dir[2]) > r )
    return false;

    //l.cross(z-axis)?

    r = box.corner.Get(0)*fabs(dir[1]) + box.corner.Get(1)*fabs(dir[0]);

    if( fabs(t[0]*dir[1] - t[1]*dir[0]) > r )
    return false;

    return true;
}

bool Tests::Intersects(const Box& box, const Ray& ray) {
    throw NotImplemented();
}


bool Tests::Intersects(const Sphere& sphere, const Vector<3,float> point) {
    throw NotImplemented();
}

bool Tests::Intersects(const Sphere& sphere, const Square& square) {
    Vector<3,float> scenter( square.GetCenter().Get(0), 0, square.GetCenter().Get(1) );
    float ssize = square.GetHalfSize();
    Vector<3,float> max = (scenter + ssize) + sphere.GetRadius();
    Vector<3,float> min = (scenter - square.GetHalfSize()) - sphere.GetRadius();
    Vector<3,float> center = sphere.GetCenter();
    if( center[0] <= max[0] && center[1] <= max[1] && center[2] <= max[2] )
        if( center[0] >= min[0] && center[1] >= min[1] && center[2] >= min[2] )
            return true;
    return false;
}

bool Tests::Intersects(const Sphere& sphere, const Plane& plane) {
    throw NotImplemented();
}

bool Tests::Intersects(const Sphere& sphere, const Line& line) { 
    throw NotImplemented();
}

/**
 * Test if sphere intersects with a ray.
 *
 * Inspired by http://local.wasp.uwa.edu.au/~pbourke/geometry/sphereline/.
 * 
 * @param sphere Sphere to test for intersection.
 * @param ray Ray to test for intersection.
 */
bool Tests::Intersects(const Sphere& sphere, const Ray& ray) {
    float radius = sphere.diameter * 0.5;

    float a = ray.dir * ray.dir;
    float b = 2*(ray.dir * (ray.point - sphere.center));
    float c = sphere.center*sphere.center + ray.point*ray.point 
        - 2*(sphere.center*ray.point) - radius*radius;

    if (b*b-4*a*c < 0)
        return false; 
    return true;
}


/**
 * Test if point is contained in the square.
 *
 * @param point Point to test for containment.
 * @return True if contained.
 */
bool Tests::Intersects(const Square& square, const Vector<3,float> point) {
    float x, z;
    x = point.Get(0) - square.center.Get(0);
    z = point.Get(2) - square.center.Get(1);
    return (fabs(x) <= square.hsize &&
            fabs(z) <= square.hsize);
}

bool Tests::Intersects(const Square& square, const Plane& plane) {
    throw NotImplemented();
}

/**
 * Test if a line intersects with the square.
 * This is also true if the hole line is contained within the square.
 *
 * @param line Line to test for intersection.
 * @return True if intersecting.
 */
bool Tests::Intersects(const Square& square, const Line& line) {
    // test end points
    if (Intersects(square, line.point1) ||
        Intersects(square, line.point2))
        return true;
    // project the line to the x-z plane
    Line l(line);
    l.point1[1] = 0;
    l.point2[1] = 0;
    for (unsigned int i=0; i<square.sides.size(); i++)
        if (Intersects(*square.sides[i], l))
            return true;
    return false;
}

bool Tests::Intersects(const Square& square, const Ray& ray) {
    throw NotImplemented();
}


bool Tests::Intersects(const Plane& plane, const Vector<3,float> point) {
    throw NotImplemented();
}

/**
 * // from: http://softsurfer.com/Archive/algorithm_0104/algorithm_0104B.htm
 */
bool Tests::Intersects(const Plane& plane, const Line& line, float* i) {
    Vector<3,float> p0 = line.point1;
    Vector<3,float> p1 = line.point2;
    Vector<3,float> v0 = plane.GetPointOnPlane();
    
    Vector<3,float> n = plane.GetNormal();
    float denom = n * (p1-p0);
    if (fabs(denom) < 0.01) return false;
    float sI = (n * (v0-p0))/denom;
    if (0>sI || sI>1)
        return false;
    if (i!=NULL)
        *i = sI;
    return true;
}
    
/*
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/planeline/
 * 
 * @todo if the ray lies on the plane then the function return false.
 */
bool Tests::Intersects(const Plane& plane, const Ray& ray, Vector<3,float>* point) {
    float denom = plane.normal * ray.dir;
    if (denom == 0.0) 
        return false;
    if (!point) return true;
    float u = (plane.normal * (plane.point-ray.point)) / denom;  
    *point = ray.point + (ray.dir * u);
    return true;
}


bool Tests::Intersects(const Line& line, const Vector<3,float> point) {
    throw NotImplemented();
}

bool Tests::Intersects(const Line& line, const Ray& ray) {
    throw NotImplemented();
}

    
bool Tests::Intersects(const Ray& ray, const Vector<3,float> point) {
    throw NotImplemented();
}


// **** inlined methods with arguments reversed ****
bool Tests::Intersects(const Vector<3,float> point, const Box& box) {
    return Intersects(box, point);
}

bool Tests::Intersects(const Sphere& sphere, const Box& box) {
    return Intersects(box, sphere);
}

bool Tests::Intersects(const Square& square, const Box& box) {
    return Intersects(box, square);
}

bool Tests::Intersects(const Plane& plane, const Box& box) {
    return Intersects(box, plane);
}

bool Tests::Intersects(const Line& line, const Box& box) {
    return Intersects(box, line);
}

bool Tests::Intersects(const Ray& ray, const Box& box) {
    return Intersects(box, ray);
}


bool Tests::Intersects(const Vector<3,float> point, const Sphere& sphere) {
    return Intersects(sphere, point);
}

bool Tests::Intersects(const Square& square, const Sphere& sphere) {
    return Intersects(sphere, square);
}

bool Tests::Intersects(const Plane& plane, const Sphere& sphere) {
    return Intersects(sphere, plane);
}

bool Tests::Intersects(const Line& line, const Sphere& sphere) {
    return Intersects(sphere, line);
}

bool Tests::Intersects(const Ray& ray, const Sphere& sphere) {
    return Intersects(sphere, ray);
}


bool Tests::Intersects(const Vector<3,float> point, const Square& square) {
    return Intersects(square, point);
}

bool Tests::Intersects(const Plane& plane, const Square& square) {
    return Intersects(square, plane);
}

bool Tests::Intersects(const Line& line, const Square& square) {
    return Intersects(square, line);
}

bool Tests::Intersects(const Ray& ray, const Square& square) {
    return Intersects(square, ray);
}

    
bool Tests::Intersects(const Vector<3,float> point, const Plane& plane) {
    return Intersects(plane, point);
}

bool Tests::Intersects(const Line& line, const Plane& plane) {
    return Intersects(plane, line);
}

bool Tests::Intersects(const Ray& ray, const Plane& plane, Vector<3,float>* point) {
    return Intersects(plane, ray, point);
}


bool Tests::Intersects(const Vector<3,float> point, const Line& line) {
    return Intersects(line, point);
}

bool Tests::Intersects(const Ray& ray, const Line& line) {
    return Intersects(line, ray);
}

    
bool Tests::Intersects(const Vector<3,float> point, const Ray& ray) {
    return Intersects(ray, point);
}

} // NS Geometry
} // NS OpenEngine
