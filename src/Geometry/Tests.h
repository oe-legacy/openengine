// Geometry subsystem.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_TESTS_H_
#define _GEOMETRY_TESTS_H_

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
class Line;
class Plane;
class Ray;
class Polygon;

using OpenEngine::Math::Vector;

/**
 * Tests on geometry.
 * This class contains static methods for doing various tests on
 * geometry structures, such as intersection tests.
 *
 * It is possible to do intersection tests on
 * every combination of geometric shapes. 
 * Example: 
 * @code 
 * Box box;
 * Line line;
 * // given two geometric objects we can test for intersection
 * bool b = Geometry::Tests::Intersects(box, line);
 * // argument order is not important!
 * b = Geometry::Tests::Intersects(line, box);
 * @endcode
 * The same methods can be used to calculate the actual 
 * intersection. Example:
 * @code 
 * Box box1;
 * Box box2;
 * Vector<3,float> p;
 * Square s;
 * // if we pass pointers to the correct intersection types as arguments.
 * // one of these will be updated to contain the actual intersection.
 * bool b = Geometry::Tests::Intersects(box, line, &p, &s);
 * if (b) {
 *   // if boxes intersected in a point then p contains this point.
 *   // if boxes intersected in a square then s contains this square.
 * }
 * else {
 *   // boxes does not intersect so neither p nor s has been modified.
 * }
 * @endcode
 * @todo Many intersection tests and actual intersection calculations
 * has not been implemented and will throw a NotImplemented exception.
 * @class Tests Tests.h Geometry/Tests.h
 */
class Tests {
public:
    Tests();
    virtual ~Tests();

    // ******* every possible intersection tests ********

    static bool Intersects(const Box&       box1, const Box&       box2);
    static bool Intersects(const Sphere& sphere1, const Sphere& sphere2);
    static bool Intersects(const Square& square1, const Square& square2);
    static bool Intersects(const Plane&   plane1, const Plane&   plane2);
    static bool Intersects(const Line&     line1, const Line&     line2);
    static bool Intersects(const Ray&       ray1, const Ray&       ray2);

    static bool Intersects(const Box& box, const Vector<3,float> point);
    static bool Intersects(const Box& box, const Sphere&        sphere);
    static bool Intersects(const Box& box, const Square&        square);
    static bool Intersects(const Box& box, const Plane& plane, Polygon* output = NULL);
    static bool Intersects(const Box& box, const Line&            line);
    static bool Intersects(const Box& box, const Ray&              ray);

    static bool Intersects(const Sphere& sphere, const Vector<3,float> point);
    static bool Intersects(const Sphere& sphere, const Square&        square);
    static bool Intersects(const Sphere& sphere, const Plane&          plane);
    static bool Intersects(const Sphere& sphere, const Line&            line);
    static bool Intersects(const Sphere& sphere, const Ray&              ray);

    static bool Intersects(const Square& square, const Vector<3,float> point);
    static bool Intersects(const Square& square, const Plane&          plane);
    static bool Intersects(const Square& square, const Line&            line);
    static bool Intersects(const Square& square, const Ray&              ray);

    static bool Intersects(const Plane& plane, const Vector<3,float> point);
    static bool Intersects(const Plane& plane, const Line&            line, float* i = NULL);
    static bool Intersects(const Plane& plane, const Ray&              ray, Vector<3,float>* point = NULL);

    static bool Intersects(const Line& line, const Vector<3,float> point);
    static bool Intersects(const Line& line, const Ray&              ray);
    
    static bool Intersects(const Ray& ray, const Vector<3,float> point);

    // same methods with arguments reversed
    static bool Intersects(const Vector<3,float> point, const Box& box);
    static bool Intersects(const Sphere&        sphere, const Box& box);
    static bool Intersects(const Square&        square, const Box& box);
    static bool Intersects(const Plane&          plane, const Box& box);
    static bool Intersects(const Line&            line, const Box& box);
    static bool Intersects(const Ray&              ray, const Box& box);

    static bool Intersects(const Vector<3,float> point, const Sphere& sphere);
    static bool Intersects(const Square&        square, const Sphere& sphere);
    static bool Intersects(const Plane&          plane, const Sphere& sphere);
    static bool Intersects(const Line&            line, const Sphere& sphere);
    static bool Intersects(const Ray&              ray, const Sphere& sphere);

    static bool Intersects(const Vector<3,float> point, const Square& square);
    static bool Intersects(const Plane&          plane, const Square& square);
    static bool Intersects(const Line&            line, const Square& square);
    static bool Intersects(const Ray&              ray, const Square& square);
    
    static bool Intersects(const Vector<3,float> point, const Plane& plane);
    static bool Intersects(const Line&            line, const Plane& plane);
    static bool Intersects(const Ray&              ray, const Plane& plane, Vector<3,float>* point = NULL);

    static bool Intersects(const Vector<3,float> point, const Line& line);
    static bool Intersects(const Ray&              ray, const Line& line);
    
    static bool Intersects(const Vector<3,float> point, const Ray& ray);
};

} // NS Geometry
} // NS OpenEngine

#endif // _GEOMETRY_TESTS_H_
