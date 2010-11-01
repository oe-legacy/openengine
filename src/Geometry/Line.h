// Line.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_LINE_H_
#define _GEOMETRY_LINE_H_

#include <Math/Vector.h>
#include <sstream>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * Line.  
 * Represented by two endpoints. This is identical to a line
 * segment in mathematics. For an infinite line see Ray.h 
 *
 * @see Ray 
 * @class Line Line.h Geometry/Line.h
 */
class Line {
public:

    Vector<3,float> point1;     //!< first endpoint of line
    Vector<3,float> point2;     //!< second endpoint of line

    Line(Vector<3,float> point1, Vector<3,float> point2);
    ~Line();

    float Distance(Line line) const;
    Line* ShortestLineBetweenRays( Vector<3,float> direction1, Vector<3,float> pointOnLine1,
                                   Vector<3,float> direction2, Vector<3,float> pointOnLine2 ) const;
    Line* ShortestLineBetweenLineAndRay( Vector<3,float> direction, Vector<3,float> pointOnLine) const;
    Line* ShortestLineBetweenLines( Line line ) const;

    std::string ToString() const;
};

/**
 * Stream operator to ease the use of ToString method.
 */
/*
std::ostream& operator<<(std::ostream& os, const Line l) {
    os<<l.ToString();
    return os;
}
*/

} //NS Geometry
} //NS OpenEngine

#endif // _GEOMETRY_LINE_H_
