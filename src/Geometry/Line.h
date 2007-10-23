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

#include <Geometry/Geometry.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

/**
 * Line.
 * A plane is defined by two points in space.
 *
 * @class Line Line.h Geometry/Line.h
 */
class Line : public Geometry {
public:

    Vector<3,float> point1;     //!< first endpoint of line
    Vector<3,float> point2;     //!< second endpoint of line

    Line(Vector<3,float> point1, Vector<3,float> point2);
    ~Line();

    bool Intersects(const Line line);
    float Distance(Line line);
    Line* ShortestLineBetweenRays( Vector<3,float> direction1, Vector<3,float> pointOnLine1,
                                   Vector<3,float> direction2, Vector<3,float> pointOnLine2 );
    Line* ShortestLineBetweenLineAndRay( Vector<3,float> direction, Vector<3,float> pointOnLine);
    Line* ShortestLineBetweenLines( Line line );

};

} //NS Geometry
} //NS OpenEngine

#endif // _GEOMETRY_LINE_H_
