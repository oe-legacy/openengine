// Line.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Line.h>
#include <Math/Math.h>
#include <Logging/Logger.h>

using OpenEngine::Math::EPS;

namespace OpenEngine {
namespace Geometry {

/**
 * Line constructor.
 *
 * @param point1 First endpoint of line
 * @param point2 Second endpoint of line
 */
Line::Line(Vector<3,float> point1, Vector<3,float> point2) 
    : point1(point1), point2(point2) {

}

/**
 * Default destructor
 */
Line::~Line() {

}

/**
 * Shortest distance between two lines.
 *
 * @todo When would we not be able to find the distance between two lines?
 *
 * @param line Line to get distance to.
 * @return Distance to line, -1 if not distance could be calculated.
 */
float Line::Distance(Line line) const {
    Line* slbl = this->ShortestLineBetweenLines(line);
    if (slbl == NULL)
        return -1;
    return (slbl->point1 - slbl->point2).GetLength();
}

/**
 * Calculate the line segment that is the shortest route between the line rays
 * (represented by a direction vectors and points on the lines)
 *
 * from: http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline3d/
 *
 * Calculate the line segment PaPb that is the shortest route between
 * two lines P1P2 and P3P4. Calculate also the values of mua and mub where
 *    Pa = P1 + mua (P2 - P1)
 *    Pb = P3 + mub (P4 - P3)
 * Return NULL if no solution exists.
 *
 * @param direction1 Direction of first ray
 * @param pointOnLine1 Point on the first ray's path
 * @param direction2 Direction of second ray
 * @param pointOnLine2 Point on the second ray's path
 * @return Shortest line or NULL if no solution exists
 */
Line* Line::ShortestLineBetweenRays(Vector<3,float> direction1, Vector<3,float> pointOnLine1,
                                    Vector<3,float> direction2, Vector<3,float> pointOnLine2) const {
    Vector<3,float> p21 = direction1;
    Vector<3,float> p43 = direction2;
    Vector<3,float> p1 = pointOnLine1;
    Vector<3,float> p3 = pointOnLine2;

    if( fabs(p21[0]) < EPS && fabs(p21[1]) < EPS && fabs(p21[2]) < EPS){
        logger.warning << "p21 < EPS" << logger.end;
        return NULL;
    }
    if( fabs(p43[0]) < EPS && fabs(p43[1]) < EPS && fabs(p43[2]) < EPS){
        logger.warning << "p43 < EPS" << logger.end;
        return NULL;
    }

    double d2121 = p21 * p21;
    double d4321 = p43 * p21;
    double d4343 = p43 * p43;
    double denom = d2121 * d4343 - d4321 * d4321;
    if( fabs(denom) < EPS ){
        logger.warning << "fabs(denom) < EPS" << logger.end;
        return NULL;
    }
    Vector<3,float> p13 = p1 - p3;
    double d1321 = p13 * p21;
    double d1343 = p13 * p43;
    double numer = d1343 * d4321 - d1321 * d4343;

    double mua = numer / denom;
    double mub = (d1343 + d4321 * (mua)) / d4343;
    
    Vector<3,float> pa = p1 + p21 * mua;
    Vector<3,float> pb = p3 + p43 * mub;
    return new Line(pa, pb);
}

/**
 * Calculate the line segment that is the shortest route between the line ray
 * (represented by a direction vector and a point on the line) and a line segment
 *
 * @param direction Direction of ray
 * @param pointOnLine Point on the ray path
 * @return Shortest line from line to ray
 */
Line* Line::ShortestLineBetweenLineAndRay(Vector<3,float> direction, Vector<3,float> pointOnLine) const {
    return ShortestLineBetweenRays(this->point2 - this->point1, this->point1, direction, pointOnLine);
}

/**
 * Calculate the line segment that is the shortest route between two line segments
 *
 * @param line Line
 * @return Shortest line between the two lines.
 */
Line* Line::ShortestLineBetweenLines(Line line) const {
    return ShortestLineBetweenRays(this->point2 - this->point1, this->point1,
                                   line.point2  - line.point1, line.point1);
}

std::string Line::ToString() const {
    std::stringstream ss;
	ss << "(" << point1 << "," << point2 << ")";
	return ss.str();
}

} //NS Geometry
} //NS OpenEngine
